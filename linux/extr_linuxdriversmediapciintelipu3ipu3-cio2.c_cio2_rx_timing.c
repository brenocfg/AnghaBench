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
typedef  int u32 ;
typedef  scalar_t__ s64 ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ LIMIT_SHIFT ; 
 scalar_t__ S32_MAX ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static s32 cio2_rx_timing(s32 a, s32 b, s64 freq, int def)
{
	const u32 accinv = 16; /* invert of counter resolution */
	const u32 uiinv = 500000000; /* 1e9 / 2 */
	s32 r;

	freq >>= LIMIT_SHIFT;

	if (WARN_ON(freq <= 0 || freq > S32_MAX))
		return def;
	/*
	 * b could be 0, -2 or -8, so |accinv * b| is always
	 * less than (1 << ds) and thus |r| < 500000000.
	 */
	r = accinv * b * (uiinv >> LIMIT_SHIFT);
	r = r / (s32)freq;
	/* max value of a is 95 */
	r += accinv * a;

	return r;
}