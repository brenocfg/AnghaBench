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
 int ENOSPC ; 
 int bitmap_find_next_zero_area (unsigned long*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set (unsigned long*,int,int) ; 
 int gcd (int,int) ; 

__attribute__((used)) static int pmap_schedule(unsigned long *map, int bits_per_period,
			 int periods_in_map, int num_bits,
			 int interval, int start, bool only_one_period)
{
	int interval_bits;
	int to_reserve;
	int first_end;
	int i;

	if (num_bits > bits_per_period)
		return -ENOSPC;

	/* Adjust interval as per description */
	interval = gcd(interval, periods_in_map);

	interval_bits = bits_per_period * interval;
	to_reserve = periods_in_map / interval;

	/* If start has gotten us past interval then we can't schedule */
	if (start >= interval_bits)
		return -ENOSPC;

	if (only_one_period)
		/* Must fit within same period as start; end at begin of next */
		first_end = (start / bits_per_period + 1) * bits_per_period;
	else
		/* Can fit anywhere in the first interval */
		first_end = interval_bits;

	/*
	 * We'll try to pick the first repetition, then see if that time
	 * is free for each of the subsequent repetitions.  If it's not
	 * we'll adjust the start time for the next search of the first
	 * repetition.
	 */
	while (start + num_bits <= first_end) {
		int end;

		/* Need to stay within this period */
		end = (start / bits_per_period + 1) * bits_per_period;

		/* Look for num_bits us in this microframe starting at start */
		start = bitmap_find_next_zero_area(map, end, start, num_bits,
						   0);

		/*
		 * We should get start >= end if we fail.  We might be
		 * able to check the next microframe depending on the
		 * interval, so continue on (start already updated).
		 */
		if (start >= end) {
			start = end;
			continue;
		}

		/* At this point we have a valid point for first one */
		for (i = 1; i < to_reserve; i++) {
			int ith_start = start + interval_bits * i;
			int ith_end = end + interval_bits * i;
			int ret;

			/* Use this as a dumb "check if bits are 0" */
			ret = bitmap_find_next_zero_area(
				map, ith_start + num_bits, ith_start, num_bits,
				0);

			/* We got the right place, continue checking */
			if (ret == ith_start)
				continue;

			/* Move start up for next time and exit for loop */
			ith_start = bitmap_find_next_zero_area(
				map, ith_end, ith_start, num_bits, 0);
			if (ith_start >= ith_end)
				/* Need a while new period next time */
				start = end;
			else
				start = ith_start - interval_bits * i;
			break;
		}

		/* If didn't exit the for loop with a break, we have success */
		if (i == to_reserve)
			break;
	}

	if (start + num_bits > first_end)
		return -ENOSPC;

	for (i = 0; i < to_reserve; i++) {
		int ith_start = start + interval_bits * i;

		bitmap_set(map, ith_start, num_bits);
	}

	return start;
}