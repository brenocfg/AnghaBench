#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int min; } ;

/* Variables and functions */
 TYPE_1__ powernv_pstate_info ; 
 scalar_t__ ramp_down_percent (unsigned int) ; 

__attribute__((used)) static inline int calc_global_pstate(unsigned int elapsed_time,
				     int highest_lpstate_idx,
				     int local_pstate_idx)
{
	int index_diff;

	/*
	 * Using ramp_down_percent we get the percentage of rampdown
	 * that we are expecting to be dropping. Difference between
	 * highest_lpstate_idx and powernv_pstate_info.min will give a absolute
	 * number of how many pstates we will drop eventually by the end of
	 * 5 seconds, then just scale it get the number pstates to be dropped.
	 */
	index_diff =  ((int)ramp_down_percent(elapsed_time) *
			(powernv_pstate_info.min - highest_lpstate_idx)) / 100;

	/* Ensure that global pstate is >= to local pstate */
	if (highest_lpstate_idx + index_diff >= local_pstate_idx)
		return local_pstate_idx;
	else
		return highest_lpstate_idx + index_diff;
}