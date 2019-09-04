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
 int /*<<< orphan*/  BUG_ON (unsigned long) ; 
 int CACHE_LINE_SIZE ; 
 unsigned long MAX_RANGE_SIZE ; 
 int PAGE_SIZE ; 

__attribute__((used)) static unsigned long calc_range_end(unsigned long start, unsigned long end)
{
	unsigned long range_end;

	BUG_ON(start & (CACHE_LINE_SIZE - 1));
	BUG_ON(end & (CACHE_LINE_SIZE - 1));

	/*
	 * Try to process all cache lines between 'start' and 'end'.
	 */
	range_end = end;

	/*
	 * Limit the number of cache lines processed at once,
	 * since cache range operations stall the CPU pipeline
	 * until completion.
	 */
	if (range_end > start + MAX_RANGE_SIZE)
		range_end = start + MAX_RANGE_SIZE;

	/*
	 * Cache range operations can't straddle a page boundary.
	 */
	if (range_end > (start | (PAGE_SIZE - 1)) + 1)
		range_end = (start | (PAGE_SIZE - 1)) + 1;

	return range_end;
}