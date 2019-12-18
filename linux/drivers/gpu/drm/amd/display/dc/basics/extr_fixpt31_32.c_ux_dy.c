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

/* Variables and functions */
 unsigned int FIXED31_32_BITS_PER_FRACTIONAL_PART ; 
 long long FRACTIONAL_PART_MASK ; 
 unsigned int GET_INTEGER_PART (long long) ; 

__attribute__((used)) static inline unsigned int ux_dy(
	long long value,
	unsigned int integer_bits,
	unsigned int fractional_bits)
{
	/* 1. create mask of integer part */
	unsigned int result = (1 << integer_bits) - 1;
	/* 2. mask out fractional part */
	unsigned int fractional_part = FRACTIONAL_PART_MASK & value;
	/* 3. shrink fixed point integer part to be of integer_bits width*/
	result &= GET_INTEGER_PART(value);
	/* 4. make space for fractional part to be filled in after integer */
	result <<= fractional_bits;
	/* 5. shrink fixed point fractional part to of fractional_bits width*/
	fractional_part >>= FIXED31_32_BITS_PER_FRACTIONAL_PART - fractional_bits;
	/* 6. merge the result */
	return result | fractional_part;
}