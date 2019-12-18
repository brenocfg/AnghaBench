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
struct smmu_pmu {int dummy; } ;
struct hw_perf_event {int idx; scalar_t__ state; } ;
struct perf_event {struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  smmu_pmu_counter_enable (struct smmu_pmu*,int) ; 
 int /*<<< orphan*/  smmu_pmu_set_period (struct smmu_pmu*,struct hw_perf_event*) ; 
 struct smmu_pmu* to_smmu_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smmu_pmu_event_start(struct perf_event *event, int flags)
{
	struct smmu_pmu *smmu_pmu = to_smmu_pmu(event->pmu);
	struct hw_perf_event *hwc = &event->hw;
	int idx = hwc->idx;

	hwc->state = 0;

	smmu_pmu_set_period(smmu_pmu, hwc);

	smmu_pmu_counter_enable(smmu_pmu, idx);
}