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
typedef  long s32 ;
typedef  int s16 ;

/* Variables and functions */

__attribute__((used)) static long zl6100_l2d(s16 l)
{
	s16 exponent;
	s32 mantissa;
	long val;

	exponent = l >> 11;
	mantissa = ((s16)((l & 0x7ff) << 5)) >> 5;

	val = mantissa;

	/* scale result to milli-units */
	val = val * 1000L;

	if (exponent >= 0)
		val <<= exponent;
	else
		val >>= -exponent;

	return val;
}