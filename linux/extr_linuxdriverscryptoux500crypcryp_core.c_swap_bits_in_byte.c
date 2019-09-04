#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static inline u8 swap_bits_in_byte(u8 b)
{
#define R_SHIFT_4_MASK  0xc0 /* Bits 6 and 7, right shift 4 */
#define R_SHIFT_2_MASK  0x28 /* (After right shift 4) Bits 3 and 5,
				  right shift 2 */
#define R_SHIFT_1_MASK  0x1e /* (After right shift 2) Bits 1-4,
				  right shift 1 */
#define L_SHIFT_4_MASK  0x03 /* Bits 0 and 1, left shift 4 */
#define L_SHIFT_2_MASK  0x14 /* (After left shift 4) Bits 2 and 4,
				  left shift 2 */
#define L_SHIFT_1_MASK  0x78 /* (After left shift 1) Bits 3-6,
				  left shift 1 */

	u8 n1;
	u8 n2;

	/* Swap most significant nibble */
	/* Right shift 4, bits 6 and 7 */
	n1 = ((b  & R_SHIFT_4_MASK) >> 4) | (b  & ~(R_SHIFT_4_MASK >> 4));
	/* Right shift 2, bits 3 and 5 */
	n1 = ((n1 & R_SHIFT_2_MASK) >> 2) | (n1 & ~(R_SHIFT_2_MASK >> 2));
	/* Right shift 1, bits 1-4 */
	n1 = (n1  & R_SHIFT_1_MASK) >> 1;

	/* Swap least significant nibble */
	/* Left shift 4, bits 0 and 1 */
	n2 = ((b  & L_SHIFT_4_MASK) << 4) | (b  & ~(L_SHIFT_4_MASK << 4));
	/* Left shift 2, bits 2 and 4 */
	n2 = ((n2 & L_SHIFT_2_MASK) << 2) | (n2 & ~(L_SHIFT_2_MASK << 2));
	/* Left shift 1, bits 3-6 */
	n2 = (n2  & L_SHIFT_1_MASK) << 1;

	return n1 | n2;
}