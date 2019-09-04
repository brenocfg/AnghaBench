#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct perf_guest_switch_msr {int host; int guest; int /*<<< orphan*/  msr; } ;
struct TYPE_5__ {scalar_t__ exclude_guest; scalar_t__ exclude_host; } ;
struct TYPE_4__ {int config; } ;
struct perf_event {TYPE_2__ attr; TYPE_1__ hw; } ;
struct cpu_hw_events {int /*<<< orphan*/  active_mask; struct perf_event** events; struct perf_guest_switch_msr* guest_switch_msrs; } ;
struct TYPE_6__ {int num_counters; } ;

/* Variables and functions */
 int ARCH_PERFMON_EVENTSEL_ENABLE ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 TYPE_3__ x86_pmu ; 
 int /*<<< orphan*/  x86_pmu_config_addr (int) ; 

__attribute__((used)) static struct perf_guest_switch_msr *core_guest_get_msrs(int *nr)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	struct perf_guest_switch_msr *arr = cpuc->guest_switch_msrs;
	int idx;

	for (idx = 0; idx < x86_pmu.num_counters; idx++)  {
		struct perf_event *event = cpuc->events[idx];

		arr[idx].msr = x86_pmu_config_addr(idx);
		arr[idx].host = arr[idx].guest = 0;

		if (!test_bit(idx, cpuc->active_mask))
			continue;

		arr[idx].host = arr[idx].guest =
			event->hw.config | ARCH_PERFMON_EVENTSEL_ENABLE;

		if (event->attr.exclude_host)
			arr[idx].host &= ~ARCH_PERFMON_EVENTSEL_ENABLE;
		else if (event->attr.exclude_guest)
			arr[idx].guest &= ~ARCH_PERFMON_EVENTSEL_ENABLE;
	}

	*nr = x86_pmu.num_counters;
	return arr;
}