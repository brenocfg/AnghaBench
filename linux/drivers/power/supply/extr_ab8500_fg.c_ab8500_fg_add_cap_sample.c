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
typedef  scalar_t__ time64_t ;
struct ab8500_fg_avg_cap {scalar_t__* time_stamps; size_t pos; int sum; int* samples; int nbr_samples; int avg; } ;
struct ab8500_fg {struct ab8500_fg_avg_cap avg_cap; } ;

/* Variables and functions */
 int NBR_AVG_SAMPLES ; 
 scalar_t__ VALID_CAPACITY_SEC ; 
 scalar_t__ ktime_get_boottime_seconds () ; 

__attribute__((used)) static int ab8500_fg_add_cap_sample(struct ab8500_fg *di, int sample)
{
	time64_t now = ktime_get_boottime_seconds();
	struct ab8500_fg_avg_cap *avg = &di->avg_cap;

	do {
		avg->sum += sample - avg->samples[avg->pos];
		avg->samples[avg->pos] = sample;
		avg->time_stamps[avg->pos] = now;
		avg->pos++;

		if (avg->pos == NBR_AVG_SAMPLES)
			avg->pos = 0;

		if (avg->nbr_samples < NBR_AVG_SAMPLES)
			avg->nbr_samples++;

		/*
		 * Check the time stamp for each sample. If too old,
		 * replace with latest sample
		 */
	} while (now - VALID_CAPACITY_SEC > avg->time_stamps[avg->pos]);

	avg->avg = avg->sum / avg->nbr_samples;

	return avg->avg;
}