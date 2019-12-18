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

__attribute__((used)) static int max44009_lux_raw(u8 hi, u8 lo)
{
	int mantissa;
	int exponent;

	/*
	 * The mantissa consists of the low nibble of the Lux High Byte
	 * and the low nibble of the Lux Low Byte.
	 */
	mantissa = ((hi & 0xf) << 4) | (lo & 0xf);

	/* The exponent byte is just the upper nibble of the Lux High Byte */
	exponent = (hi >> 4) & 0xf;

	/*
	 * The exponent value is base 2 to the power of the raw exponent byte.
	 */
	exponent = 1 << exponent;

	return exponent * mantissa;
}