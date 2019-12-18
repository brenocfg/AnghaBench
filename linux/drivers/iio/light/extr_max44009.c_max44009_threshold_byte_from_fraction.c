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
 int EINVAL ; 
 int MAX44009_FRACT_MULT ; 
 int MAX44009_MAXIMUM_THRESHOLD ; 
 int MAX44009_SCALE_DENOMINATOR ; 
 int MAX44009_SCALE_NUMERATOR ; 

__attribute__((used)) static int max44009_threshold_byte_from_fraction(int integral, int fractional)
{
	int mantissa, exp;

	if ((integral <= 0 && fractional <= 0) ||
	     integral > MAX44009_MAXIMUM_THRESHOLD ||
	     (integral == MAX44009_MAXIMUM_THRESHOLD && fractional != 0))
		return -EINVAL;

	/* Reverse scaling of fixed-point integral */
	mantissa = integral * MAX44009_SCALE_DENOMINATOR;
	mantissa /= MAX44009_SCALE_NUMERATOR;

	/* Reverse scaling of fixed-point fractional */
	mantissa += fractional / MAX44009_FRACT_MULT *
		    (MAX44009_SCALE_DENOMINATOR / MAX44009_SCALE_NUMERATOR);

	for (exp = 0; mantissa > 0xff; exp++)
		mantissa >>= 1;

	mantissa >>= 4;
	mantissa &= 0xf;
	exp <<= 4;

	return exp | mantissa;
}