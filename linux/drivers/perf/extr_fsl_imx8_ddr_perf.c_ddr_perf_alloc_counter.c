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
typedef  size_t u32 ;
struct ddr_pmu {int /*<<< orphan*/ ** events; } ;

/* Variables and functions */
 size_t ENOENT ; 
 size_t EVENT_CYCLES_COUNTER ; 
 int EVENT_CYCLES_ID ; 
 int NUM_COUNTERS ; 

__attribute__((used)) static u32 ddr_perf_alloc_counter(struct ddr_pmu *pmu, int event)
{
	int i;

	/*
	 * Always map cycle event to counter 0
	 * Cycles counter is dedicated for cycle event
	 * can't used for the other events
	 */
	if (event == EVENT_CYCLES_ID) {
		if (pmu->events[EVENT_CYCLES_COUNTER] == NULL)
			return EVENT_CYCLES_COUNTER;
		else
			return -ENOENT;
	}

	for (i = 1; i < NUM_COUNTERS; i++) {
		if (pmu->events[i] == NULL)
			return i;
	}

	return -ENOENT;
}