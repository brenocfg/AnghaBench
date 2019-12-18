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
struct smmu_pmu {struct perf_event** events; } ;
struct hw_perf_event {int idx; int state; int /*<<< orphan*/  prev_count; } ;
struct perf_event {int /*<<< orphan*/  pmu; struct hw_perf_event hw; } ;

/* Variables and functions */
 int PERF_EF_START ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  smmu_pmu_event_start (struct perf_event*,int) ; 
 int smmu_pmu_get_event_idx (struct smmu_pmu*,struct perf_event*) ; 
 int /*<<< orphan*/  smmu_pmu_interrupt_enable (struct smmu_pmu*,int) ; 
 struct smmu_pmu* to_smmu_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smmu_pmu_event_add(struct perf_event *event, int flags)
{
	struct hw_perf_event *hwc = &event->hw;
	int idx;
	struct smmu_pmu *smmu_pmu = to_smmu_pmu(event->pmu);

	idx = smmu_pmu_get_event_idx(smmu_pmu, event);
	if (idx < 0)
		return idx;

	hwc->idx = idx;
	hwc->state = PERF_HES_STOPPED | PERF_HES_UPTODATE;
	smmu_pmu->events[idx] = event;
	local64_set(&hwc->prev_count, 0);

	smmu_pmu_interrupt_enable(smmu_pmu, idx);

	if (flags & PERF_EF_START)
		smmu_pmu_event_start(event, flags);

	/* Propagate changes to the userspace mapping. */
	perf_event_update_userpage(event);

	return 0;
}