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
struct smmu_pmu {int /*<<< orphan*/  used_counters; int /*<<< orphan*/ ** events; } ;
struct hw_perf_event {int idx; } ;
struct perf_event {int /*<<< orphan*/  pmu; struct hw_perf_event hw; } ;

/* Variables and functions */
 int PERF_EF_UPDATE ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  smmu_pmu_event_stop (struct perf_event*,int) ; 
 int /*<<< orphan*/  smmu_pmu_interrupt_disable (struct smmu_pmu*,int) ; 
 struct smmu_pmu* to_smmu_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smmu_pmu_event_del(struct perf_event *event, int flags)
{
	struct hw_perf_event *hwc = &event->hw;
	struct smmu_pmu *smmu_pmu = to_smmu_pmu(event->pmu);
	int idx = hwc->idx;

	smmu_pmu_event_stop(event, flags | PERF_EF_UPDATE);
	smmu_pmu_interrupt_disable(smmu_pmu, idx);
	smmu_pmu->events[idx] = NULL;
	clear_bit(idx, smmu_pmu->used_counters);

	perf_event_update_userpage(event);
}