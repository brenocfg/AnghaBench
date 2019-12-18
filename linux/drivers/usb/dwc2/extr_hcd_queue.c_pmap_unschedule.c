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
 int /*<<< orphan*/  bitmap_clear (unsigned long*,int,int) ; 
 int gcd (int,int) ; 

__attribute__((used)) static void pmap_unschedule(unsigned long *map, int bits_per_period,
			    int periods_in_map, int num_bits,
			    int interval, int start)
{
	int interval_bits;
	int to_release;
	int i;

	/* Adjust interval as per description in pmap_schedule() */
	interval = gcd(interval, periods_in_map);

	interval_bits = bits_per_period * interval;
	to_release = periods_in_map / interval;

	for (i = 0; i < to_release; i++) {
		int ith_start = start + interval_bits * i;

		bitmap_clear(map, ith_start, num_bits);
	}
}