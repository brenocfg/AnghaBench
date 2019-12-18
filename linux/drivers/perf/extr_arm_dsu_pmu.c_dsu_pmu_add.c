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
struct perf_event {struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;
struct dsu_hw_events {struct perf_event** events; } ;
struct dsu_pmu {int /*<<< orphan*/  associated_cpus; struct dsu_hw_events hw_events; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  PERF_EF_RELOAD ; 
 int PERF_EF_START ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cpumask_test_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dsu_pmu_get_event_idx (struct dsu_hw_events*,struct perf_event*) ; 
 int /*<<< orphan*/  dsu_pmu_start (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 struct dsu_pmu* to_dsu_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsu_pmu_add(struct perf_event *event, int flags)
{
	struct dsu_pmu *dsu_pmu = to_dsu_pmu(event->pmu);
	struct dsu_hw_events *hw_events = &dsu_pmu->hw_events;
	struct hw_perf_event *hwc = &event->hw;
	int idx;

	if (WARN_ON_ONCE(!cpumask_test_cpu(smp_processor_id(),
					   &dsu_pmu->associated_cpus)))
		return -ENOENT;

	idx = dsu_pmu_get_event_idx(hw_events, event);
	if (idx < 0)
		return idx;

	hwc->idx = idx;
	hw_events->events[idx] = event;
	hwc->state = PERF_HES_STOPPED | PERF_HES_UPTODATE;

	if (flags & PERF_EF_START)
		dsu_pmu_start(event, PERF_EF_RELOAD);

	perf_event_update_userpage(event);
	return 0;
}