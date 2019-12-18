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
typedef  int u16 ;
typedef  int s16 ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (long,int) ; 
 long MAX_MANTISSA ; 
 long MIN_MANTISSA ; 

__attribute__((used)) static u16 zl6100_d2l(long val)
{
	s16 exponent = 0, mantissa;
	bool negative = false;

	/* simple case */
	if (val == 0)
		return 0;

	if (val < 0) {
		negative = true;
		val = -val;
	}

	/* Reduce large mantissa until it fits into 10 bit */
	while (val >= MAX_MANTISSA && exponent < 15) {
		exponent++;
		val >>= 1;
	}
	/* Increase small mantissa to improve precision */
	while (val < MIN_MANTISSA && exponent > -15) {
		exponent--;
		val <<= 1;
	}

	/* Convert mantissa from milli-units to units */
	mantissa = DIV_ROUND_CLOSEST(val, 1000);

	/* Ensure that resulting number is within range */
	if (mantissa > 0x3ff)
		mantissa = 0x3ff;

	/* restore sign */
	if (negative)
		mantissa = -mantissa;

	/* Convert to 5 bit exponent, 11 bit mantissa */
	return (mantissa & 0x7ff) | ((exponent << 11) & 0xf800);
}