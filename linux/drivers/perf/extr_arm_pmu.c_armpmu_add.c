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
struct pmu_hw_events {struct perf_event** events; } ;
struct hw_perf_event {int idx; int state; } ;
struct perf_event {struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;
struct arm_pmu {int (* get_event_idx ) (struct pmu_hw_events*,struct perf_event*) ;int /*<<< orphan*/  (* disable ) (struct perf_event*) ;int /*<<< orphan*/  supported_cpus; int /*<<< orphan*/  hw_events; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  PERF_EF_RELOAD ; 
 int PERF_EF_START ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  armpmu_start (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_test_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int stub1 (struct pmu_hw_events*,struct perf_event*) ; 
 int /*<<< orphan*/  stub2 (struct perf_event*) ; 
 struct pmu_hw_events* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 struct arm_pmu* to_arm_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
armpmu_add(struct perf_event *event, int flags)
{
	struct arm_pmu *armpmu = to_arm_pmu(event->pmu);
	struct pmu_hw_events *hw_events = this_cpu_ptr(armpmu->hw_events);
	struct hw_perf_event *hwc = &event->hw;
	int idx;

	/* An event following a process won't be stopped earlier */
	if (!cpumask_test_cpu(smp_processor_id(), &armpmu->supported_cpus))
		return -ENOENT;

	/* If we don't have a space for the counter then finish early. */
	idx = armpmu->get_event_idx(hw_events, event);
	if (idx < 0)
		return idx;

	/*
	 * If there is an event in the counter we are going to use then make
	 * sure it is disabled.
	 */
	event->hw.idx = idx;
	armpmu->disable(event);
	hw_events->events[idx] = event;

	hwc->state = PERF_HES_STOPPED | PERF_HES_UPTODATE;
	if (flags & PERF_EF_START)
		armpmu_start(event, PERF_EF_RELOAD);

	/* Propagate our changes to the userspace mapping. */
	perf_event_update_userpage(event);

	return 0;
}