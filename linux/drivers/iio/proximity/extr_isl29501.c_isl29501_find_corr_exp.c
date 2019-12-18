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

__attribute__((used)) static unsigned int isl29501_find_corr_exp(unsigned int val,
					   unsigned int max_exp,
					   unsigned int max_mantissa)
{
	unsigned int exp = 1;

	/*
	 * Correction coefficients are represented under
	 * mantissa * 2^exponent form, where mantissa and exponent
	 * are stored in two separate registers of the sensor.
	 *
	 * Compute and return the lowest exponent such as:
	 *	     mantissa = value / 2^exponent
	 *
	 *  where mantissa < max_mantissa.
	 */
	if (val <= max_mantissa)
		return 0;

	while ((val >> exp) > max_mantissa) {
		exp++;

		if (exp > max_exp)
			return max_exp;
	}

	return exp;
}