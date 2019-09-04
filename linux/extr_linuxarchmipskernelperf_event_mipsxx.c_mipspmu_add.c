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
struct hw_perf_event {int idx; int state; } ;
struct perf_event {int /*<<< orphan*/  pmu; struct hw_perf_event hw; } ;
struct cpu_hw_events {struct perf_event** events; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EF_RELOAD ; 
 int PERF_EF_START ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  mipspmu_start (struct perf_event*,int /*<<< orphan*/ ) ; 
 int mipsxx_pmu_alloc_counter (struct cpu_hw_events*,struct hw_perf_event*) ; 
 int /*<<< orphan*/  mipsxx_pmu_disable_event (int) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  perf_pmu_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_pmu_enable (int /*<<< orphan*/ ) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mipspmu_add(struct perf_event *event, int flags)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	struct hw_perf_event *hwc = &event->hw;
	int idx;
	int err = 0;

	perf_pmu_disable(event->pmu);

	/* To look for a free counter for this event. */
	idx = mipsxx_pmu_alloc_counter(cpuc, hwc);
	if (idx < 0) {
		err = idx;
		goto out;
	}

	/*
	 * If there is an event in the counter we are going to use then
	 * make sure it is disabled.
	 */
	event->hw.idx = idx;
	mipsxx_pmu_disable_event(idx);
	cpuc->events[idx] = event;

	hwc->state = PERF_HES_STOPPED | PERF_HES_UPTODATE;
	if (flags & PERF_EF_START)
		mipspmu_start(event, PERF_EF_RELOAD);

	/* Propagate our changes to the userspace mapping. */
	perf_event_update_userpage(event);

out:
	perf_pmu_enable(event->pmu);
	return err;
}