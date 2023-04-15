#pragma once

#include <cstring>
#include <iostream>

#if (defined __INTEL_COMPILER) && (defined WIN32)
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

// See: https://github.com/lemire/streamvbyte
static const uint8_t encode_shuf_lut[64*16] = {
    0x00, 0x04, 0x08, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x04, 0x08, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x04, 0x08, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x08, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x04, 0x05, 0x08, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x04, 0x05, 0x08, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x04, 0x05, 0x08, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x08, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x04, 0x05, 0x06, 0x08, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x04, 0x05, 0x06, 0x08, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x04, 0x05, 0x06, 0x08, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x08, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x04, 0x05, 0x06, 0x07, 0x08, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x04, 0x05, 0x06, 0x07, 0x08, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x04, 0x05, 0x06, 0x07, 0x08, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF,
    0x00, 0x04, 0x08, 0x09, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x04, 0x08, 0x09, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x04, 0x08, 0x09, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x08, 0x09, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x04, 0x05, 0x08, 0x09, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x04, 0x05, 0x08, 0x09, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x04, 0x05, 0x08, 0x09, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x08, 0x09, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x04, 0x05, 0x06, 0x08, 0x09, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x04, 0x05, 0x06, 0x08, 0x09, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x04, 0x05, 0x06, 0x08, 0x09, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x08, 0x09, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF,
    0x00, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF,
    0x00, 0x04, 0x08, 0x09, 0x0A, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x04, 0x08, 0x09, 0x0A, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x04, 0x08, 0x09, 0x0A, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x08, 0x09, 0x0A, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x04, 0x05, 0x08, 0x09, 0x0A, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x04, 0x05, 0x08, 0x09, 0x0A, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x04, 0x05, 0x08, 0x09, 0x0A, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x08, 0x09, 0x0A, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF,
    0x00, 0x04, 0x05, 0x06, 0x08, 0x09, 0x0A, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x04, 0x05, 0x06, 0x08, 0x09, 0x0A, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x04, 0x05, 0x06, 0x08, 0x09, 0x0A, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x08, 0x09, 0x0A, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF,
    0x00, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF,
    0x00, 0x04, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x04, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x04, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF,
    0x00, 0x04, 0x05, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x04, 0x05, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x04, 0x05, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF,
    0x00, 0x04, 0x05, 0x06, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x04, 0x05, 0x06, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x04, 0x05, 0x06, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF,
    0x00, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
};

// See: https://github.com/lemire/streamvbyte
static const uint8_t len_lut[256] = {
    4,  5,  6,  7,  5,  6,  7,  8,  6,  7,  8,  9,  7,  8,  9, 10,
    5,  6,  7,  8,  6,  7,  8,  9,  7,  8,  9, 10,  8,  9, 10, 11,
    6,  7,  8,  9,  7,  8,  9, 10,  8,  9, 10, 11,  9, 10, 11, 12,
    7,  8,  9, 10,  8,  9, 10, 11,  9, 10, 11, 12, 10, 11, 12, 13,
    5,  6,  7,  8,  6,  7,  8,  9,  7,  8,  9, 10,  8,  9, 10, 11,
    6,  7,  8,  9,  7,  8,  9, 10,  8,  9, 10, 11,  9, 10, 11, 12,
    7,  8,  9, 10,  8,  9, 10, 11,  9, 10, 11, 12, 10, 11, 12, 13,
    8,  9, 10, 11,  9, 10, 11, 12, 10, 11, 12, 13, 11, 12, 13, 14,
    6,  7,  8,  9,  7,  8,  9, 10,  8,  9, 10, 11,  9, 10, 11, 12,
    7,  8,  9, 10,  8,  9, 10, 11,  9, 10, 11, 12, 10, 11, 12, 13,
    8,  9, 10, 11,  9, 10, 11, 12, 10, 11, 12, 13, 11, 12, 13, 14,
    9, 10, 11, 12, 10, 11, 12, 13, 11, 12, 13, 14, 12, 13, 14, 15,
    7,  8,  9, 10,  8,  9, 10, 11,  9, 10, 11, 12, 10, 11, 12, 13,
    8,  9, 10, 11,  9, 10, 11, 12, 10, 11, 12, 13, 11, 12, 13, 14,
    9, 10, 11, 12, 10, 11, 12, 13, 11, 12, 13, 14, 12, 13, 14, 15,
    10, 11, 12, 13, 11, 12, 13, 14, 12, 13, 14, 15, 13, 14, 15, 16,
};

// See: https://github.com/lemire/streamvbyte
static int8_t decode_shuffleTable[256][16] = {
 {  0, -1, -1, -1,  1, -1, -1, -1,  2, -1, -1, -1,  3, -1, -1, -1 },    // 0000
 {  0,  1, -1, -1,  2, -1, -1, -1,  3, -1, -1, -1,  4, -1, -1, -1 },    // 1000
 {  0,  1,  2, -1,  3, -1, -1, -1,  4, -1, -1, -1,  5, -1, -1, -1 },    // 2000
 {  0,  1,  2,  3,  4, -1, -1, -1,  5, -1, -1, -1,  6, -1, -1, -1 },    // 3000
 {  0, -1, -1, -1,  1,  2, -1, -1,  3, -1, -1, -1,  4, -1, -1, -1 },    // 0100
 {  0,  1, -1, -1,  2,  3, -1, -1,  4, -1, -1, -1,  5, -1, -1, -1 },    // 1100
 {  0,  1,  2, -1,  3,  4, -1, -1,  5, -1, -1, -1,  6, -1, -1, -1 },    // 2100
 {  0,  1,  2,  3,  4,  5, -1, -1,  6, -1, -1, -1,  7, -1, -1, -1 },    // 3100
 {  0, -1, -1, -1,  1,  2,  3, -1,  4, -1, -1, -1,  5, -1, -1, -1 },    // 0200
 {  0,  1, -1, -1,  2,  3,  4, -1,  5, -1, -1, -1,  6, -1, -1, -1 },    // 1200
 {  0,  1,  2, -1,  3,  4,  5, -1,  6, -1, -1, -1,  7, -1, -1, -1 },    // 2200
 {  0,  1,  2,  3,  4,  5,  6, -1,  7, -1, -1, -1,  8, -1, -1, -1 },    // 3200
 {  0, -1, -1, -1,  1,  2,  3,  4,  5, -1, -1, -1,  6, -1, -1, -1 },    // 0300
 {  0,  1, -1, -1,  2,  3,  4,  5,  6, -1, -1, -1,  7, -1, -1, -1 },    // 1300
 {  0,  1,  2, -1,  3,  4,  5,  6,  7, -1, -1, -1,  8, -1, -1, -1 },    // 2300
 {  0,  1,  2,  3,  4,  5,  6,  7,  8, -1, -1, -1,  9, -1, -1, -1 },    // 3300
 {  0, -1, -1, -1,  1, -1, -1, -1,  2,  3, -1, -1,  4, -1, -1, -1 },    // 0010
 {  0,  1, -1, -1,  2, -1, -1, -1,  3,  4, -1, -1,  5, -1, -1, -1 },    // 1010
 {  0,  1,  2, -1,  3, -1, -1, -1,  4,  5, -1, -1,  6, -1, -1, -1 },    // 2010
 {  0,  1,  2,  3,  4, -1, -1, -1,  5,  6, -1, -1,  7, -1, -1, -1 },    // 3010
 {  0, -1, -1, -1,  1,  2, -1, -1,  3,  4, -1, -1,  5, -1, -1, -1 },    // 0110
 {  0,  1, -1, -1,  2,  3, -1, -1,  4,  5, -1, -1,  6, -1, -1, -1 },    // 1110
 {  0,  1,  2, -1,  3,  4, -1, -1,  5,  6, -1, -1,  7, -1, -1, -1 },    // 2110
 {  0,  1,  2,  3,  4,  5, -1, -1,  6,  7, -1, -1,  8, -1, -1, -1 },    // 3110
 {  0, -1, -1, -1,  1,  2,  3, -1,  4,  5, -1, -1,  6, -1, -1, -1 },    // 0210
 {  0,  1, -1, -1,  2,  3,  4, -1,  5,  6, -1, -1,  7, -1, -1, -1 },    // 1210
 {  0,  1,  2, -1,  3,  4,  5, -1,  6,  7, -1, -1,  8, -1, -1, -1 },    // 2210
 {  0,  1,  2,  3,  4,  5,  6, -1,  7,  8, -1, -1,  9, -1, -1, -1 },    // 3210
 {  0, -1, -1, -1,  1,  2,  3,  4,  5,  6, -1, -1,  7, -1, -1, -1 },    // 0310
 {  0,  1, -1, -1,  2,  3,  4,  5,  6,  7, -1, -1,  8, -1, -1, -1 },    // 1310
 {  0,  1,  2, -1,  3,  4,  5,  6,  7,  8, -1, -1,  9, -1, -1, -1 },    // 2310
 {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, 10, -1, -1, -1 },    // 3310
 {  0, -1, -1, -1,  1, -1, -1, -1,  2,  3,  4, -1,  5, -1, -1, -1 },    // 0020
 {  0,  1, -1, -1,  2, -1, -1, -1,  3,  4,  5, -1,  6, -1, -1, -1 },    // 1020
 {  0,  1,  2, -1,  3, -1, -1, -1,  4,  5,  6, -1,  7, -1, -1, -1 },    // 2020
 {  0,  1,  2,  3,  4, -1, -1, -1,  5,  6,  7, -1,  8, -1, -1, -1 },    // 3020
 {  0, -1, -1, -1,  1,  2, -1, -1,  3,  4,  5, -1,  6, -1, -1, -1 },    // 0120
 {  0,  1, -1, -1,  2,  3, -1, -1,  4,  5,  6, -1,  7, -1, -1, -1 },    // 1120
 {  0,  1,  2, -1,  3,  4, -1, -1,  5,  6,  7, -1,  8, -1, -1, -1 },    // 2120
 {  0,  1,  2,  3,  4,  5, -1, -1,  6,  7,  8, -1,  9, -1, -1, -1 },    // 3120
 {  0, -1, -1, -1,  1,  2,  3, -1,  4,  5,  6, -1,  7, -1, -1, -1 },    // 0220
 {  0,  1, -1, -1,  2,  3,  4, -1,  5,  6,  7, -1,  8, -1, -1, -1 },    // 1220
 {  0,  1,  2, -1,  3,  4,  5, -1,  6,  7,  8, -1,  9, -1, -1, -1 },    // 2220
 {  0,  1,  2,  3,  4,  5,  6, -1,  7,  8,  9, -1, 10, -1, -1, -1 },    // 3220
 {  0, -1, -1, -1,  1,  2,  3,  4,  5,  6,  7, -1,  8, -1, -1, -1 },    // 0320
 {  0,  1, -1, -1,  2,  3,  4,  5,  6,  7,  8, -1,  9, -1, -1, -1 },    // 1320
 {  0,  1,  2, -1,  3,  4,  5,  6,  7,  8,  9, -1, 10, -1, -1, -1 },    // 2320
 {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, -1, 11, -1, -1, -1 },    // 3320
 {  0, -1, -1, -1,  1, -1, -1, -1,  2,  3,  4,  5,  6, -1, -1, -1 },    // 0030
 {  0,  1, -1, -1,  2, -1, -1, -1,  3,  4,  5,  6,  7, -1, -1, -1 },    // 1030
 {  0,  1,  2, -1,  3, -1, -1, -1,  4,  5,  6,  7,  8, -1, -1, -1 },    // 2030
 {  0,  1,  2,  3,  4, -1, -1, -1,  5,  6,  7,  8,  9, -1, -1, -1 },    // 3030
 {  0, -1, -1, -1,  1,  2, -1, -1,  3,  4,  5,  6,  7, -1, -1, -1 },    // 0130
 {  0,  1, -1, -1,  2,  3, -1, -1,  4,  5,  6,  7,  8, -1, -1, -1 },    // 1130
 {  0,  1,  2, -1,  3,  4, -1, -1,  5,  6,  7,  8,  9, -1, -1, -1 },    // 2130
 {  0,  1,  2,  3,  4,  5, -1, -1,  6,  7,  8,  9, 10, -1, -1, -1 },    // 3130
 {  0, -1, -1, -1,  1,  2,  3, -1,  4,  5,  6,  7,  8, -1, -1, -1 },    // 0230
 {  0,  1, -1, -1,  2,  3,  4, -1,  5,  6,  7,  8,  9, -1, -1, -1 },    // 1230
 {  0,  1,  2, -1,  3,  4,  5, -1,  6,  7,  8,  9, 10, -1, -1, -1 },    // 2230
 {  0,  1,  2,  3,  4,  5,  6, -1,  7,  8,  9, 10, 11, -1, -1, -1 },    // 3230
 {  0, -1, -1, -1,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1 },    // 0330
 {  0,  1, -1, -1,  2,  3,  4,  5,  6,  7,  8,  9, 10, -1, -1, -1 },    // 1330
 {  0,  1,  2, -1,  3,  4,  5,  6,  7,  8,  9, 10, 11, -1, -1, -1 },    // 2330
 {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, -1, -1, -1 },    // 3330
 {  0, -1, -1, -1,  1, -1, -1, -1,  2, -1, -1, -1,  3,  4, -1, -1 },    // 0001
 {  0,  1, -1, -1,  2, -1, -1, -1,  3, -1, -1, -1,  4,  5, -1, -1 },    // 1001
 {  0,  1,  2, -1,  3, -1, -1, -1,  4, -1, -1, -1,  5,  6, -1, -1 },    // 2001
 {  0,  1,  2,  3,  4, -1, -1, -1,  5, -1, -1, -1,  6,  7, -1, -1 },    // 3001
 {  0, -1, -1, -1,  1,  2, -1, -1,  3, -1, -1, -1,  4,  5, -1, -1 },    // 0101
 {  0,  1, -1, -1,  2,  3, -1, -1,  4, -1, -1, -1,  5,  6, -1, -1 },    // 1101
 {  0,  1,  2, -1,  3,  4, -1, -1,  5, -1, -1, -1,  6,  7, -1, -1 },    // 2101
 {  0,  1,  2,  3,  4,  5, -1, -1,  6, -1, -1, -1,  7,  8, -1, -1 },    // 3101
 {  0, -1, -1, -1,  1,  2,  3, -1,  4, -1, -1, -1,  5,  6, -1, -1 },    // 0201
 {  0,  1, -1, -1,  2,  3,  4, -1,  5, -1, -1, -1,  6,  7, -1, -1 },    // 1201
 {  0,  1,  2, -1,  3,  4,  5, -1,  6, -1, -1, -1,  7,  8, -1, -1 },    // 2201
 {  0,  1,  2,  3,  4,  5,  6, -1,  7, -1, -1, -1,  8,  9, -1, -1 },    // 3201
 {  0, -1, -1, -1,  1,  2,  3,  4,  5, -1, -1, -1,  6,  7, -1, -1 },    // 0301
 {  0,  1, -1, -1,  2,  3,  4,  5,  6, -1, -1, -1,  7,  8, -1, -1 },    // 1301
 {  0,  1,  2, -1,  3,  4,  5,  6,  7, -1, -1, -1,  8,  9, -1, -1 },    // 2301
 {  0,  1,  2,  3,  4,  5,  6,  7,  8, -1, -1, -1,  9, 10, -1, -1 },    // 3301
 {  0, -1, -1, -1,  1, -1, -1, -1,  2,  3, -1, -1,  4,  5, -1, -1 },    // 0011
 {  0,  1, -1, -1,  2, -1, -1, -1,  3,  4, -1, -1,  5,  6, -1, -1 },    // 1011
 {  0,  1,  2, -1,  3, -1, -1, -1,  4,  5, -1, -1,  6,  7, -1, -1 },    // 2011
 {  0,  1,  2,  3,  4, -1, -1, -1,  5,  6, -1, -1,  7,  8, -1, -1 },    // 3011
 {  0, -1, -1, -1,  1,  2, -1, -1,  3,  4, -1, -1,  5,  6, -1, -1 },    // 0111
 {  0,  1, -1, -1,  2,  3, -1, -1,  4,  5, -1, -1,  6,  7, -1, -1 },    // 1111
 {  0,  1,  2, -1,  3,  4, -1, -1,  5,  6, -1, -1,  7,  8, -1, -1 },    // 2111
 {  0,  1,  2,  3,  4,  5, -1, -1,  6,  7, -1, -1,  8,  9, -1, -1 },    // 3111
 {  0, -1, -1, -1,  1,  2,  3, -1,  4,  5, -1, -1,  6,  7, -1, -1 },    // 0211
 {  0,  1, -1, -1,  2,  3,  4, -1,  5,  6, -1, -1,  7,  8, -1, -1 },    // 1211
 {  0,  1,  2, -1,  3,  4,  5, -1,  6,  7, -1, -1,  8,  9, -1, -1 },    // 2211
 {  0,  1,  2,  3,  4,  5,  6, -1,  7,  8, -1, -1,  9, 10, -1, -1 },    // 3211
 {  0, -1, -1, -1,  1,  2,  3,  4,  5,  6, -1, -1,  7,  8, -1, -1 },    // 0311
 {  0,  1, -1, -1,  2,  3,  4,  5,  6,  7, -1, -1,  8,  9, -1, -1 },    // 1311
 {  0,  1,  2, -1,  3,  4,  5,  6,  7,  8, -1, -1,  9, 10, -1, -1 },    // 2311
 {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, 10, 11, -1, -1 },    // 3311
 {  0, -1, -1, -1,  1, -1, -1, -1,  2,  3,  4, -1,  5,  6, -1, -1 },    // 0021
 {  0,  1, -1, -1,  2, -1, -1, -1,  3,  4,  5, -1,  6,  7, -1, -1 },    // 1021
 {  0,  1,  2, -1,  3, -1, -1, -1,  4,  5,  6, -1,  7,  8, -1, -1 },    // 2021
 {  0,  1,  2,  3,  4, -1, -1, -1,  5,  6,  7, -1,  8,  9, -1, -1 },    // 3021
 {  0, -1, -1, -1,  1,  2, -1, -1,  3,  4,  5, -1,  6,  7, -1, -1 },    // 0121
 {  0,  1, -1, -1,  2,  3, -1, -1,  4,  5,  6, -1,  7,  8, -1, -1 },    // 1121
 {  0,  1,  2, -1,  3,  4, -1, -1,  5,  6,  7, -1,  8,  9, -1, -1 },    // 2121
 {  0,  1,  2,  3,  4,  5, -1, -1,  6,  7,  8, -1,  9, 10, -1, -1 },    // 3121
 {  0, -1, -1, -1,  1,  2,  3, -1,  4,  5,  6, -1,  7,  8, -1, -1 },    // 0221
 {  0,  1, -1, -1,  2,  3,  4, -1,  5,  6,  7, -1,  8,  9, -1, -1 },    // 1221
 {  0,  1,  2, -1,  3,  4,  5, -1,  6,  7,  8, -1,  9, 10, -1, -1 },    // 2221
 {  0,  1,  2,  3,  4,  5,  6, -1,  7,  8,  9, -1, 10, 11, -1, -1 },    // 3221
 {  0, -1, -1, -1,  1,  2,  3,  4,  5,  6,  7, -1,  8,  9, -1, -1 },    // 0321
 {  0,  1, -1, -1,  2,  3,  4,  5,  6,  7,  8, -1,  9, 10, -1, -1 },    // 1321
 {  0,  1,  2, -1,  3,  4,  5,  6,  7,  8,  9, -1, 10, 11, -1, -1 },    // 2321
 {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, -1, 11, 12, -1, -1 },    // 3321
 {  0, -1, -1, -1,  1, -1, -1, -1,  2,  3,  4,  5,  6,  7, -1, -1 },    // 0031
 {  0,  1, -1, -1,  2, -1, -1, -1,  3,  4,  5,  6,  7,  8, -1, -1 },    // 1031
 {  0,  1,  2, -1,  3, -1, -1, -1,  4,  5,  6,  7,  8,  9, -1, -1 },    // 2031
 {  0,  1,  2,  3,  4, -1, -1, -1,  5,  6,  7,  8,  9, 10, -1, -1 },    // 3031
 {  0, -1, -1, -1,  1,  2, -1, -1,  3,  4,  5,  6,  7,  8, -1, -1 },    // 0131
 {  0,  1, -1, -1,  2,  3, -1, -1,  4,  5,  6,  7,  8,  9, -1, -1 },    // 1131
 {  0,  1,  2, -1,  3,  4, -1, -1,  5,  6,  7,  8,  9, 10, -1, -1 },    // 2131
 {  0,  1,  2,  3,  4,  5, -1, -1,  6,  7,  8,  9, 10, 11, -1, -1 },    // 3131
 {  0, -1, -1, -1,  1,  2,  3, -1,  4,  5,  6,  7,  8,  9, -1, -1 },    // 0231
 {  0,  1, -1, -1,  2,  3,  4, -1,  5,  6,  7,  8,  9, 10, -1, -1 },    // 1231
 {  0,  1,  2, -1,  3,  4,  5, -1,  6,  7,  8,  9, 10, 11, -1, -1 },    // 2231
 {  0,  1,  2,  3,  4,  5,  6, -1,  7,  8,  9, 10, 11, 12, -1, -1 },    // 3231
 {  0, -1, -1, -1,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, -1, -1 },    // 0331
 {  0,  1, -1, -1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, -1, -1 },    // 1331
 {  0,  1,  2, -1,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, -1, -1 },    // 2331
 {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, -1, -1 },    // 3331
 {  0, -1, -1, -1,  1, -1, -1, -1,  2, -1, -1, -1,  3,  4,  5, -1 },    // 0002
 {  0,  1, -1, -1,  2, -1, -1, -1,  3, -1, -1, -1,  4,  5,  6, -1 },    // 1002
 {  0,  1,  2, -1,  3, -1, -1, -1,  4, -1, -1, -1,  5,  6,  7, -1 },    // 2002
 {  0,  1,  2,  3,  4, -1, -1, -1,  5, -1, -1, -1,  6,  7,  8, -1 },    // 3002
 {  0, -1, -1, -1,  1,  2, -1, -1,  3, -1, -1, -1,  4,  5,  6, -1 },    // 0102
 {  0,  1, -1, -1,  2,  3, -1, -1,  4, -1, -1, -1,  5,  6,  7, -1 },    // 1102
 {  0,  1,  2, -1,  3,  4, -1, -1,  5, -1, -1, -1,  6,  7,  8, -1 },    // 2102
 {  0,  1,  2,  3,  4,  5, -1, -1,  6, -1, -1, -1,  7,  8,  9, -1 },    // 3102
 {  0, -1, -1, -1,  1,  2,  3, -1,  4, -1, -1, -1,  5,  6,  7, -1 },    // 0202
 {  0,  1, -1, -1,  2,  3,  4, -1,  5, -1, -1, -1,  6,  7,  8, -1 },    // 1202
 {  0,  1,  2, -1,  3,  4,  5, -1,  6, -1, -1, -1,  7,  8,  9, -1 },    // 2202
 {  0,  1,  2,  3,  4,  5,  6, -1,  7, -1, -1, -1,  8,  9, 10, -1 },    // 3202
 {  0, -1, -1, -1,  1,  2,  3,  4,  5, -1, -1, -1,  6,  7,  8, -1 },    // 0302
 {  0,  1, -1, -1,  2,  3,  4,  5,  6, -1, -1, -1,  7,  8,  9, -1 },    // 1302
 {  0,  1,  2, -1,  3,  4,  5,  6,  7, -1, -1, -1,  8,  9, 10, -1 },    // 2302
 {  0,  1,  2,  3,  4,  5,  6,  7,  8, -1, -1, -1,  9, 10, 11, -1 },    // 3302
 {  0, -1, -1, -1,  1, -1, -1, -1,  2,  3, -1, -1,  4,  5,  6, -1 },    // 0012
 {  0,  1, -1, -1,  2, -1, -1, -1,  3,  4, -1, -1,  5,  6,  7, -1 },    // 1012
 {  0,  1,  2, -1,  3, -1, -1, -1,  4,  5, -1, -1,  6,  7,  8, -1 },    // 2012
 {  0,  1,  2,  3,  4, -1, -1, -1,  5,  6, -1, -1,  7,  8,  9, -1 },    // 3012
 {  0, -1, -1, -1,  1,  2, -1, -1,  3,  4, -1, -1,  5,  6,  7, -1 },    // 0112
 {  0,  1, -1, -1,  2,  3, -1, -1,  4,  5, -1, -1,  6,  7,  8, -1 },    // 1112
 {  0,  1,  2, -1,  3,  4, -1, -1,  5,  6, -1, -1,  7,  8,  9, -1 },    // 2112
 {  0,  1,  2,  3,  4,  5, -1, -1,  6,  7, -1, -1,  8,  9, 10, -1 },    // 3112
 {  0, -1, -1, -1,  1,  2,  3, -1,  4,  5, -1, -1,  6,  7,  8, -1 },    // 0212
 {  0,  1, -1, -1,  2,  3,  4, -1,  5,  6, -1, -1,  7,  8,  9, -1 },    // 1212
 {  0,  1,  2, -1,  3,  4,  5, -1,  6,  7, -1, -1,  8,  9, 10, -1 },    // 2212
 {  0,  1,  2,  3,  4,  5,  6, -1,  7,  8, -1, -1,  9, 10, 11, -1 },    // 3212
 {  0, -1, -1, -1,  1,  2,  3,  4,  5,  6, -1, -1,  7,  8,  9, -1 },    // 0312
 {  0,  1, -1, -1,  2,  3,  4,  5,  6,  7, -1, -1,  8,  9, 10, -1 },    // 1312
 {  0,  1,  2, -1,  3,  4,  5,  6,  7,  8, -1, -1,  9, 10, 11, -1 },    // 2312
 {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, 10, 11, 12, -1 },    // 3312
 {  0, -1, -1, -1,  1, -1, -1, -1,  2,  3,  4, -1,  5,  6,  7, -1 },    // 0022
 {  0,  1, -1, -1,  2, -1, -1, -1,  3,  4,  5, -1,  6,  7,  8, -1 },    // 1022
 {  0,  1,  2, -1,  3, -1, -1, -1,  4,  5,  6, -1,  7,  8,  9, -1 },    // 2022
 {  0,  1,  2,  3,  4, -1, -1, -1,  5,  6,  7, -1,  8,  9, 10, -1 },    // 3022
 {  0, -1, -1, -1,  1,  2, -1, -1,  3,  4,  5, -1,  6,  7,  8, -1 },    // 0122
 {  0,  1, -1, -1,  2,  3, -1, -1,  4,  5,  6, -1,  7,  8,  9, -1 },    // 1122
 {  0,  1,  2, -1,  3,  4, -1, -1,  5,  6,  7, -1,  8,  9, 10, -1 },    // 2122
 {  0,  1,  2,  3,  4,  5, -1, -1,  6,  7,  8, -1,  9, 10, 11, -1 },    // 3122
 {  0, -1, -1, -1,  1,  2,  3, -1,  4,  5,  6, -1,  7,  8,  9, -1 },    // 0222
 {  0,  1, -1, -1,  2,  3,  4, -1,  5,  6,  7, -1,  8,  9, 10, -1 },    // 1222
 {  0,  1,  2, -1,  3,  4,  5, -1,  6,  7,  8, -1,  9, 10, 11, -1 },    // 2222
 {  0,  1,  2,  3,  4,  5,  6, -1,  7,  8,  9, -1, 10, 11, 12, -1 },    // 3222
 {  0, -1, -1, -1,  1,  2,  3,  4,  5,  6,  7, -1,  8,  9, 10, -1 },    // 0322
 {  0,  1, -1, -1,  2,  3,  4,  5,  6,  7,  8, -1,  9, 10, 11, -1 },    // 1322
 {  0,  1,  2, -1,  3,  4,  5,  6,  7,  8,  9, -1, 10, 11, 12, -1 },    // 2322
 {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, -1, 11, 12, 13, -1 },    // 3322
 {  0, -1, -1, -1,  1, -1, -1, -1,  2,  3,  4,  5,  6,  7,  8, -1 },    // 0032
 {  0,  1, -1, -1,  2, -1, -1, -1,  3,  4,  5,  6,  7,  8,  9, -1 },    // 1032
 {  0,  1,  2, -1,  3, -1, -1, -1,  4,  5,  6,  7,  8,  9, 10, -1 },    // 2032
 {  0,  1,  2,  3,  4, -1, -1, -1,  5,  6,  7,  8,  9, 10, 11, -1 },    // 3032
 {  0, -1, -1, -1,  1,  2, -1, -1,  3,  4,  5,  6,  7,  8,  9, -1 },    // 0132
 {  0,  1, -1, -1,  2,  3, -1, -1,  4,  5,  6,  7,  8,  9, 10, -1 },    // 1132
 {  0,  1,  2, -1,  3,  4, -1, -1,  5,  6,  7,  8,  9, 10, 11, -1 },    // 2132
 {  0,  1,  2,  3,  4,  5, -1, -1,  6,  7,  8,  9, 10, 11, 12, -1 },    // 3132
 {  0, -1, -1, -1,  1,  2,  3, -1,  4,  5,  6,  7,  8,  9, 10, -1 },    // 0232
 {  0,  1, -1, -1,  2,  3,  4, -1,  5,  6,  7,  8,  9, 10, 11, -1 },    // 1232
 {  0,  1,  2, -1,  3,  4,  5, -1,  6,  7,  8,  9, 10, 11, 12, -1 },    // 2232
 {  0,  1,  2,  3,  4,  5,  6, -1,  7,  8,  9, 10, 11, 12, 13, -1 },    // 3232
 {  0, -1, -1, -1,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, -1 },    // 0332
 {  0,  1, -1, -1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, -1 },    // 1332
 {  0,  1,  2, -1,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, -1 },    // 2332
 {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, -1 },    // 3332
 {  0, -1, -1, -1,  1, -1, -1, -1,  2, -1, -1, -1,  3,  4,  5,  6 },    // 0003
 {  0,  1, -1, -1,  2, -1, -1, -1,  3, -1, -1, -1,  4,  5,  6,  7 },    // 1003
 {  0,  1,  2, -1,  3, -1, -1, -1,  4, -1, -1, -1,  5,  6,  7,  8 },    // 2003
 {  0,  1,  2,  3,  4, -1, -1, -1,  5, -1, -1, -1,  6,  7,  8,  9 },    // 3003
 {  0, -1, -1, -1,  1,  2, -1, -1,  3, -1, -1, -1,  4,  5,  6,  7 },    // 0103
 {  0,  1, -1, -1,  2,  3, -1, -1,  4, -1, -1, -1,  5,  6,  7,  8 },    // 1103
 {  0,  1,  2, -1,  3,  4, -1, -1,  5, -1, -1, -1,  6,  7,  8,  9 },    // 2103
 {  0,  1,  2,  3,  4,  5, -1, -1,  6, -1, -1, -1,  7,  8,  9, 10 },    // 3103
 {  0, -1, -1, -1,  1,  2,  3, -1,  4, -1, -1, -1,  5,  6,  7,  8 },    // 0203
 {  0,  1, -1, -1,  2,  3,  4, -1,  5, -1, -1, -1,  6,  7,  8,  9 },    // 1203
 {  0,  1,  2, -1,  3,  4,  5, -1,  6, -1, -1, -1,  7,  8,  9, 10 },    // 2203
 {  0,  1,  2,  3,  4,  5,  6, -1,  7, -1, -1, -1,  8,  9, 10, 11 },    // 3203
 {  0, -1, -1, -1,  1,  2,  3,  4,  5, -1, -1, -1,  6,  7,  8,  9 },    // 0303
 {  0,  1, -1, -1,  2,  3,  4,  5,  6, -1, -1, -1,  7,  8,  9, 10 },    // 1303
 {  0,  1,  2, -1,  3,  4,  5,  6,  7, -1, -1, -1,  8,  9, 10, 11 },    // 2303
 {  0,  1,  2,  3,  4,  5,  6,  7,  8, -1, -1, -1,  9, 10, 11, 12 },    // 3303
 {  0, -1, -1, -1,  1, -1, -1, -1,  2,  3, -1, -1,  4,  5,  6,  7 },    // 0013
 {  0,  1, -1, -1,  2, -1, -1, -1,  3,  4, -1, -1,  5,  6,  7,  8 },    // 1013
 {  0,  1,  2, -1,  3, -1, -1, -1,  4,  5, -1, -1,  6,  7,  8,  9 },    // 2013
 {  0,  1,  2,  3,  4, -1, -1, -1,  5,  6, -1, -1,  7,  8,  9, 10 },    // 3013
 {  0, -1, -1, -1,  1,  2, -1, -1,  3,  4, -1, -1,  5,  6,  7,  8 },    // 0113
 {  0,  1, -1, -1,  2,  3, -1, -1,  4,  5, -1, -1,  6,  7,  8,  9 },    // 1113
 {  0,  1,  2, -1,  3,  4, -1, -1,  5,  6, -1, -1,  7,  8,  9, 10 },    // 2113
 {  0,  1,  2,  3,  4,  5, -1, -1,  6,  7, -1, -1,  8,  9, 10, 11 },    // 3113
 {  0, -1, -1, -1,  1,  2,  3, -1,  4,  5, -1, -1,  6,  7,  8,  9 },    // 0213
 {  0,  1, -1, -1,  2,  3,  4, -1,  5,  6, -1, -1,  7,  8,  9, 10 },    // 1213
 {  0,  1,  2, -1,  3,  4,  5, -1,  6,  7, -1, -1,  8,  9, 10, 11 },    // 2213
 {  0,  1,  2,  3,  4,  5,  6, -1,  7,  8, -1, -1,  9, 10, 11, 12 },    // 3213
 {  0, -1, -1, -1,  1,  2,  3,  4,  5,  6, -1, -1,  7,  8,  9, 10 },    // 0313
 {  0,  1, -1, -1,  2,  3,  4,  5,  6,  7, -1, -1,  8,  9, 10, 11 },    // 1313
 {  0,  1,  2, -1,  3,  4,  5,  6,  7,  8, -1, -1,  9, 10, 11, 12 },    // 2313
 {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, 10, 11, 12, 13 },    // 3313
 {  0, -1, -1, -1,  1, -1, -1, -1,  2,  3,  4, -1,  5,  6,  7,  8 },    // 0023
 {  0,  1, -1, -1,  2, -1, -1, -1,  3,  4,  5, -1,  6,  7,  8,  9 },    // 1023
 {  0,  1,  2, -1,  3, -1, -1, -1,  4,  5,  6, -1,  7,  8,  9, 10 },    // 2023
 {  0,  1,  2,  3,  4, -1, -1, -1,  5,  6,  7, -1,  8,  9, 10, 11 },    // 3023
 {  0, -1, -1, -1,  1,  2, -1, -1,  3,  4,  5, -1,  6,  7,  8,  9 },    // 0123
 {  0,  1, -1, -1,  2,  3, -1, -1,  4,  5,  6, -1,  7,  8,  9, 10 },    // 1123
 {  0,  1,  2, -1,  3,  4, -1, -1,  5,  6,  7, -1,  8,  9, 10, 11 },    // 2123
 {  0,  1,  2,  3,  4,  5, -1, -1,  6,  7,  8, -1,  9, 10, 11, 12 },    // 3123
 {  0, -1, -1, -1,  1,  2,  3, -1,  4,  5,  6, -1,  7,  8,  9, 10 },    // 0223
 {  0,  1, -1, -1,  2,  3,  4, -1,  5,  6,  7, -1,  8,  9, 10, 11 },    // 1223
 {  0,  1,  2, -1,  3,  4,  5, -1,  6,  7,  8, -1,  9, 10, 11, 12 },    // 2223
 {  0,  1,  2,  3,  4,  5,  6, -1,  7,  8,  9, -1, 10, 11, 12, 13 },    // 3223
 {  0, -1, -1, -1,  1,  2,  3,  4,  5,  6,  7, -1,  8,  9, 10, 11 },    // 0323
 {  0,  1, -1, -1,  2,  3,  4,  5,  6,  7,  8, -1,  9, 10, 11, 12 },    // 1323
 {  0,  1,  2, -1,  3,  4,  5,  6,  7,  8,  9, -1, 10, 11, 12, 13 },    // 2323
 {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, -1, 11, 12, 13, 14 },    // 3323
 {  0, -1, -1, -1,  1, -1, -1, -1,  2,  3,  4,  5,  6,  7,  8,  9 },    // 0033
 {  0,  1, -1, -1,  2, -1, -1, -1,  3,  4,  5,  6,  7,  8,  9, 10 },    // 1033
 {  0,  1,  2, -1,  3, -1, -1, -1,  4,  5,  6,  7,  8,  9, 10, 11 },    // 2033
 {  0,  1,  2,  3,  4, -1, -1, -1,  5,  6,  7,  8,  9, 10, 11, 12 },    // 3033
 {  0, -1, -1, -1,  1,  2, -1, -1,  3,  4,  5,  6,  7,  8,  9, 10 },    // 0133
 {  0,  1, -1, -1,  2,  3, -1, -1,  4,  5,  6,  7,  8,  9, 10, 11 },    // 1133
 {  0,  1,  2, -1,  3,  4, -1, -1,  5,  6,  7,  8,  9, 10, 11, 12 },    // 2133
 {  0,  1,  2,  3,  4,  5, -1, -1,  6,  7,  8,  9, 10, 11, 12, 13 },    // 3133
 {  0, -1, -1, -1,  1,  2,  3, -1,  4,  5,  6,  7,  8,  9, 10, 11 },    // 0233
 {  0,  1, -1, -1,  2,  3,  4, -1,  5,  6,  7,  8,  9, 10, 11, 12 },    // 1233
 {  0,  1,  2, -1,  3,  4,  5, -1,  6,  7,  8,  9, 10, 11, 12, 13 },    // 2233
 {  0,  1,  2,  3,  4,  5,  6, -1,  7,  8,  9, 10, 11, 12, 13, 14 },    // 3233
 {  0, -1, -1, -1,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12 },    // 0333
 {  0,  1, -1, -1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13 },    // 1333
 {  0,  1,  2, -1,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14 },    // 2333
 {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 },    // 3333
};

template <typename T>
inline static std::size_t scalar_to_zig_zag(gsl::span<std::int16_t const> input, std::array<std::uint32_t, 8>& output, T last_value)
{
    auto const size = std::min(output.size(), input.size());
    auto const shift_size = (sizeof(T)*8) - 1;
    for (std::size_t i = 0; i < size; ++i)
    {
        T const delta = input[i] - last_value;
        output[i] = (delta << 1) ^ (delta >> shift_size);
        last_value = input[i];
    }
    return size;
}

template <typename T>
inline static std::size_t zig_zag_to_scalar(gsl::span<std::uint32_t> const& input, gsl::span<std::int16_t> output, T last_value)
{
    auto const size = std::min(output.size(), input.size());
    for (std::size_t i = 0; i < size; ++i)
    {
        std::uint32_t const zig_zag = input[i];
        output[i] = ((zig_zag >> 1) ^ - (zig_zag & 1)) + last_value;
        last_value = output[i];
    }
    return size;
}

template <typename IntType, typename RegType, typename PrintType=IntType>
void dump_reg(std::ostream& str, RegType reg)
{
    union {
        RegType reg;
        IntType values[sizeof(RegType)/sizeof(IntType)];
    } conv;
    conv.reg = reg;
    
    for (auto x : conv.values)
    {
        str << (PrintType)x << " ";
    }
}

/// \brief Optimised ssse3 implementation for x64 when performing zig zag deltas.
template <>
struct StreamVByteWorkerV0<std::int16_t, true>
{
    static vbz_size_t compress(gsl::span<char const> input_bytes, gsl::span<char> output)
    {
        auto const input = input_bytes.as_span<std::int16_t const>();
        std::uint32_t size = input.size();
        if (size == 0)
        {
            return 0;
        }

        uint32_t keyLen = (size >> 2) + (((size & 3) + 3) >> 2); // 2-bits per each rounded up to byte boundry
        char *keyPtr = &output[0];
        char *dataPtr = &output[keyLen]; // variable length data after keys

        const __m128i zero = _mm_set1_epi16(0);

        auto step = 8;
        std::size_t completed = 0;

        auto prev_current = _mm_set1_epi16(0);
        for (; (completed+step) <= size; completed += step)
        {
            // load data from source short buffer
            auto current = _mm_lddqu_si128((__m128i*)(input.data() + completed));

            // Combine to find previous values
            auto prev = _mm_alignr_epi8(current, prev_current, 14);

            // Find delta between elements
            auto delta = _mm_sub_epi16(current, prev);
            prev_current = current;

            // Perform zig zag int reorganisation
            auto shl = _mm_slli_epi16(delta, 1);
            auto shr = _mm_srai_epi16(delta, 15);        
            auto xor_res = _mm_xor_si128(shl, shr);
            
            auto low = _mm_unpacklo_epi16(xor_res, zero);
            auto high = _mm_unpackhi_epi16(xor_res, zero);
            
            // Perform normal sse3 streamvbyte encode
            compress_int_registers(low, high, keyPtr, dataPtr);
        }

        std::array<std::uint32_t, 8> final_elements;
        std::int16_t last_value = completed == 0 ? 0 : input[completed-1];
        scalar_to_zig_zag(input.subspan(completed), final_elements, last_value);

        // do remaining
        uint32_t key = 0;
        for(size_t i = 0; i < (size & 7); i++)
        {
            uint32_t dw = final_elements[i];
            uint32_t symbol = (dw > 0x000000FF) + (dw > 0x0000FFFF) + (dw > 0x00FFFFFF);
            key |= symbol << (i + i);
            *((uint32_t*)dataPtr) = dw;
            dataPtr += 1 + symbol;
        }
        memcpy(keyPtr, &key, ((size & 7) + 3) >> 2);

        return dataPtr - output.begin();
    }
    
    static vbz_size_t decompress(gsl::span<char const> input, gsl::span<char> output_bytes)
    {
        auto const output = output_bytes.as_span<std::int16_t>();

        int count = output.size();
        if (count == 0)
        {
            return 0;
        }

        vbz_size_t key_byte_count = (count + 3) / 4;
        if (input.size() < key_byte_count)
        {
            return VBZ_STREAMVBYTE_INPUT_SIZE_ERROR;
        }

        // full list of keys starts
        // 2-bits per key (rounded up)
        auto keys = input.subspan(0, key_byte_count).as_span<std::uint8_t const>();
        // data starts at end of keys
        gsl::span<char const> data = input.subspan(key_byte_count);
        std::size_t key_byte_pairs = count / (4*2);    // 2 bits per int - 4 ints per byte, iterate in pairs - 8 ints at once

        std::size_t key_idx = 0;
        std::size_t output_index = 0;
        auto prev = _mm_set1_epi16(0); // previous set to 0 to begin with
        for (; key_idx < key_byte_pairs; ++key_idx)
        {
            // We'll process at max 32 bytes of input from data - if theres < than that left we need to
            // use the scalar impl
            if (data.size() < 32)
            {
                break;
            }
            
            auto const key_1 = keys[key_idx*2];
            auto data_1 = decompress_int_registers(key_1, data);

            auto const key_2 = keys[key_idx*2+1];
            auto data_2 = decompress_int_registers(key_2, data);
            
            // Now unpack the decompressed data to signed integers.
            auto const to_16_bit_left = _mm_setr_epi8(-1,-1,-1,-1,-1,-1,-1,-1, 0,1,  4,5,  8,9,  12, 13);
            auto const to_16_bit_right = _mm_setr_epi8(0,1,  4,5,  8,9,  12, 13, -1,-1,-1,-1,-1,-1,-1,-1);
            auto const left = _mm_shuffle_epi8(data_1, to_16_bit_left);
            auto const right = _mm_shuffle_epi8(data_2, to_16_bit_right);
            auto const values = _mm_alignr_epi8(right, left, 8);
            
            const __m128i mask_1 = _mm_set1_epi16(1);
            // Perform un-zig zag int reorganisation
            // (n >> 1) ^ - (n & 1)
            auto shr = _mm_srli_epi16(values, 1);
            auto neg_bit = _mm_sign_epi16(_mm_and_si128(values, mask_1), _mm_set1_epi16(-1));
            auto xor_res = _mm_xor_si128(shr, neg_bit);
        
            // Combine to find previous values
            auto zero = _mm_set1_epi16(0);
            auto cum_sum = xor_res;
            auto cum_sum_adder = xor_res;
            
            for (std::size_t i = 0; i < 7; ++i)
            {
                auto next_cum_sum_adder = _mm_alignr_epi8(cum_sum_adder, zero, 14);
                cum_sum = _mm_add_epi16(cum_sum, next_cum_sum_adder);
                cum_sum_adder = next_cum_sum_adder;
            }

            cum_sum = _mm_add_epi16(cum_sum, prev);
            _mm_storeu_si128((__m128i *)output.subspan(output_index).data(), cum_sum);

            prev = _mm_shuffle_epi8(cum_sum, _mm_setr_epi8(14, 15, 14, 15, 14, 15, 14, 15, 14, 15, 14, 15, 14, 15, 14, 15));
            output_index += 8;
        }

        auto scalar_count = count - output_index;
        if (scalar_count)
        {
            auto scalar_keys = keys.subspan(key_idx*2);
            std::size_t key_index = 0;

            std::array<std::uint32_t, 32> final_elements;
            uint8_t shift = 0;
            uint32_t key = scalar_keys[key_index++];
            
            vbz_size_t error_value = 0;
            for (uint32_t c = 0; c < scalar_count; c++) 
            {
                if (shift == 8) {
                    shift = 0;
                    key = scalar_keys[key_index++];
                }
                uint32_t val = decompress_int(data, (key >> shift) & 0x3, error_value);
                if (error_value)
                {
                    return error_value;
                }
                
                final_elements[c] = val;
                shift += 2;
            }

            std::int16_t last_value = output_index == 0 ? 0 : output.subspan(output_index - 1)[0];
            zig_zag_to_scalar(gsl::make_span(final_elements).subspan(0, scalar_count), output.subspan(output_index), last_value);

        }

        if (data.size() != 0)
        {
            return VBZ_STREAMVBYTE_STREAM_ERROR;
        }

        return output.size() * sizeof(std::int16_t);
    }

    inline static void compress_int_registers(__m128i r0, __m128i r1, char*& keyPtr, char*& dataPtr)
    {
        std::size_t keys;
        __m128i r2, r3;

        const __m128i mask_01 = _mm_set1_epi8(0x01);
        const __m128i mask_7F00 = _mm_set1_epi16(0x7F00);

        r2 = _mm_min_epu8(mask_01, r0);
        r3 = _mm_min_epu8(mask_01, r1);
        r2 = _mm_packus_epi16(r2, r3);
        r2 = _mm_min_epi16(r2, mask_01); // convert 0x01FF to 0x0101
        r2 = _mm_adds_epu16(r2, mask_7F00); // convert: 0x0101 to 0x8001, 0xFF01 to 0xFFFF
        keys = (size_t)_mm_movemask_epi8(r2);

        r2 = _mm_loadu_si128((__m128i*)&encode_shuf_lut[(keys << 4) & 0x03F0]);
        r3 = _mm_loadu_si128((__m128i*)&encode_shuf_lut[(keys >> 4) & 0x03F0]);
        r0 = _mm_shuffle_epi8(r0, r2);
        r1 = _mm_shuffle_epi8(r1, r3);

        _mm_storeu_si128((__m128i *)dataPtr, r0);
        dataPtr += len_lut[keys & 0xFF];
        _mm_storeu_si128((__m128i *)dataPtr, r1);
        dataPtr += len_lut[keys >> 8];
        
        *((uint16_t*)keyPtr) = (uint16_t)keys;
        keyPtr += 2;
    }

    inline static __m128i decompress_int_registers(uint32_t key, gsl::span<char const>& data_buffer)
    {
        uint8_t len;
        __m128i data = _mm_loadu_si128(data_buffer.subspan(0, sizeof(__m128i)).as_span<__m128i const>().data());

        uint8_t *pshuf = (uint8_t *) &decode_shuffleTable[key];
        __m128i shuf = *(__m128i *)pshuf;
        len = len_lut[key];
        
        data = _mm_shuffle_epi8(data, shuf);
        data_buffer = data_buffer.subspan(len);
        return data;
    }

    inline static std::uint32_t decompress_int(gsl::span<char const>& data_buffer, int code, vbz_size_t& error_value)
    {
        std::size_t copy_size = 0;
        if (code == 0) { // 1 byte
            copy_size = 1;
        } else if (code == 1) { // 2 bytes
            copy_size = 2;
        } else if (code == 2) { // 3 bytes
            copy_size = 3;
        } else { // code == 3
            copy_size = 4;
        }
        
        if (data_buffer.size() < copy_size)
        {
            error_value = VBZ_STREAMVBYTE_STREAM_ERROR;
            return 0;
        }
        
        std::uint32_t val = 0;
        memcpy(&val, data_buffer.data(), copy_size);
        data_buffer = data_buffer.subspan(copy_size);

        return val;
    }

    template <typename U, typename V>
    static void cast(gsl::span<U> input, gsl::span<V> output)
    {
        for (std::size_t i = 0; i < input.size(); ++i)
        {
            output[i] = input[i];
        }
    }
};
