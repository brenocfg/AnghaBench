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
struct TYPE_2__ {unsigned long config; } ;
struct perf_event {int /*<<< orphan*/  pmu; TYPE_1__ attr; } ;
struct dsu_pmu {int num_counters; } ;
struct dsu_hw_events {unsigned long* used_mask; } ;

/* Variables and functions */
 unsigned long DSU_PMU_EVT_CYCLES ; 
 int DSU_PMU_IDX_CYCLE_COUNTER ; 
 int EAGAIN ; 
 int find_first_zero_bit (unsigned long*,int) ; 
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 
 scalar_t__ test_and_set_bit (int,unsigned long*) ; 
 struct dsu_pmu* to_dsu_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsu_pmu_get_event_idx(struct dsu_hw_events *hw_events,
				 struct perf_event *event)
{
	int idx;
	unsigned long evtype = event->attr.config;
	struct dsu_pmu *dsu_pmu = to_dsu_pmu(event->pmu);
	unsigned long *used_mask = hw_events->used_mask;

	if (evtype == DSU_PMU_EVT_CYCLES) {
		if (test_and_set_bit(DSU_PMU_IDX_CYCLE_COUNTER, used_mask))
			return -EAGAIN;
		return DSU_PMU_IDX_CYCLE_COUNTER;
	}

	idx = find_first_zero_bit(used_mask, dsu_pmu->num_counters);
	if (idx >= dsu_pmu->num_counters)
		return -EAGAIN;
	set_bit(idx, hw_events->used_mask);
	return idx;
}