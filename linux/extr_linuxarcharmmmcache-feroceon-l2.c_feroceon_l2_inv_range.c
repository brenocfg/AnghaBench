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
 int CACHE_LINE_SIZE ; 
 unsigned long calc_range_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  dsb () ; 
 int /*<<< orphan*/  l2_clean_inv_pa (unsigned long) ; 
 int /*<<< orphan*/  l2_inv_pa_range (unsigned long,unsigned long) ; 

__attribute__((used)) static void feroceon_l2_inv_range(unsigned long start, unsigned long end)
{
	/*
	 * Clean and invalidate partial first cache line.
	 */
	if (start & (CACHE_LINE_SIZE - 1)) {
		l2_clean_inv_pa(start & ~(CACHE_LINE_SIZE - 1));
		start = (start | (CACHE_LINE_SIZE - 1)) + 1;
	}

	/*
	 * Clean and invalidate partial last cache line.
	 */
	if (start < end && end & (CACHE_LINE_SIZE - 1)) {
		l2_clean_inv_pa(end & ~(CACHE_LINE_SIZE - 1));
		end &= ~(CACHE_LINE_SIZE - 1);
	}

	/*
	 * Invalidate all full cache lines between 'start' and 'end'.
	 */
	while (start < end) {
		unsigned long range_end = calc_range_end(start, end);
		l2_inv_pa_range(start, range_end - CACHE_LINE_SIZE);
		start = range_end;
	}

	dsb();
}