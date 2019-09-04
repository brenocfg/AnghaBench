#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hw_perf_event {int dummy; } ;
struct cpu_hw_events {int /*<<< orphan*/  active_mask; TYPE_1__** events; } ;
struct TYPE_4__ {int num_counters; } ;
struct TYPE_3__ {struct hw_perf_event hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCH_PERFMON_EVENTSEL_ENABLE ; 
 int /*<<< orphan*/  __x86_pmu_enable_event (struct hw_perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 TYPE_2__ x86_pmu ; 

void x86_pmu_enable_all(int added)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	int idx;

	for (idx = 0; idx < x86_pmu.num_counters; idx++) {
		struct hw_perf_event *hwc = &cpuc->events[idx]->hw;

		if (!test_bit(idx, cpuc->active_mask))
			continue;

		__x86_pmu_enable_event(hwc, ARCH_PERFMON_EVENTSEL_ENABLE);
	}
}