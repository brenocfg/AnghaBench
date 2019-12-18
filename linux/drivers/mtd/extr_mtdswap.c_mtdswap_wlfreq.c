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
 unsigned int COLLECT_NONDIRTY_BASE ; 
 int COLLECT_NONDIRTY_FREQ1 ; 
 int COLLECT_NONDIRTY_FREQ2 ; 
 unsigned int MAX_ERASE_DIFF ; 

__attribute__((used)) static int mtdswap_wlfreq(unsigned int maxdiff)
{
	unsigned int h, x, y, dist, base;

	/*
	 * Calculate linear ramp down from f1 to f2 when maxdiff goes from
	 * MAX_ERASE_DIFF to MAX_ERASE_DIFF + COLLECT_NONDIRTY_BASE.  Similar
	 * to triangle with height f1 - f1 and width COLLECT_NONDIRTY_BASE.
	 */

	dist = maxdiff - MAX_ERASE_DIFF;
	if (dist > COLLECT_NONDIRTY_BASE)
		dist = COLLECT_NONDIRTY_BASE;

	/*
	 * Modelling the slop as right angular triangle with base
	 * COLLECT_NONDIRTY_BASE and height freq1 - freq2. The ratio y/x is
	 * equal to the ratio h/base.
	 */
	h = COLLECT_NONDIRTY_FREQ1 - COLLECT_NONDIRTY_FREQ2;
	base = COLLECT_NONDIRTY_BASE;

	x = dist - base;
	y = (x * h + base / 2) / base;

	return COLLECT_NONDIRTY_FREQ2 + y;
}