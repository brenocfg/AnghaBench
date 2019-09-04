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
struct pmu_hw_events {int /*<<< orphan*/  used_mask; } ;
struct hw_perf_event {unsigned long config_base; } ;
struct perf_event {struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;
struct arm_pmu {int dummy; } ;

/* Variables and functions */
 int ARMV8_IDX_CYCLE_COUNTER ; 
 unsigned long ARMV8_PMUV3_PERFCTR_CPU_CYCLES ; 
 unsigned long ARMV8_PMU_EVTYPE_EVENT ; 
 scalar_t__ armv8pmu_event_is_64bit (struct perf_event*) ; 
 int armv8pmu_get_chain_idx (struct pmu_hw_events*,struct arm_pmu*) ; 
 int armv8pmu_get_single_idx (struct pmu_hw_events*,struct arm_pmu*) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ ) ; 
 struct arm_pmu* to_arm_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int armv8pmu_get_event_idx(struct pmu_hw_events *cpuc,
				  struct perf_event *event)
{
	struct arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);
	struct hw_perf_event *hwc = &event->hw;
	unsigned long evtype = hwc->config_base & ARMV8_PMU_EVTYPE_EVENT;

	/* Always prefer to place a cycle counter into the cycle counter. */
	if (evtype == ARMV8_PMUV3_PERFCTR_CPU_CYCLES) {
		if (!test_and_set_bit(ARMV8_IDX_CYCLE_COUNTER, cpuc->used_mask))
			return ARMV8_IDX_CYCLE_COUNTER;
	}

	/*
	 * Otherwise use events counters
	 */
	if (armv8pmu_event_is_64bit(event))
		return	armv8pmu_get_chain_idx(cpuc, cpu_pmu);
	else
		return armv8pmu_get_single_idx(cpuc, cpu_pmu);
}