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
struct perf_output_handle {int dummy; } ;
struct hw_perf_event {int state; int /*<<< orphan*/  period_left; } ;
struct perf_event {struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;
struct arm_spe_pmu {int /*<<< orphan*/  handle; } ;
typedef  enum arm_spe_pmu_buf_fault_action { ____Placeholder_arm_spe_pmu_buf_fault_action } arm_spe_pmu_buf_fault_action ;

/* Variables and functions */
 int PERF_EF_UPDATE ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int SPE_PMU_BUF_FAULT_ACT_SPURIOUS ; 
 int /*<<< orphan*/  SYS_PMBSR_EL1 ; 
 int /*<<< orphan*/  SYS_PMSICR_EL1 ; 
 int /*<<< orphan*/  arm_spe_perf_aux_output_end (struct perf_output_handle*) ; 
 int arm_spe_pmu_buf_get_fault_act (struct perf_output_handle*) ; 
 int /*<<< orphan*/  arm_spe_pmu_disable_and_drain_local () ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ perf_get_aux (struct perf_output_handle*) ; 
 int /*<<< orphan*/  read_sysreg_s (int /*<<< orphan*/ ) ; 
 struct perf_output_handle* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 struct arm_spe_pmu* to_spe_pmu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_sysreg_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arm_spe_pmu_stop(struct perf_event *event, int flags)
{
	struct arm_spe_pmu *spe_pmu = to_spe_pmu(event->pmu);
	struct hw_perf_event *hwc = &event->hw;
	struct perf_output_handle *handle = this_cpu_ptr(spe_pmu->handle);

	/* If we're already stopped, then nothing to do */
	if (hwc->state & PERF_HES_STOPPED)
		return;

	/* Stop all trace generation */
	arm_spe_pmu_disable_and_drain_local();

	if (flags & PERF_EF_UPDATE) {
		/*
		 * If there's a fault pending then ensure we contain it
		 * to this buffer, since we might be on the context-switch
		 * path.
		 */
		if (perf_get_aux(handle)) {
			enum arm_spe_pmu_buf_fault_action act;

			act = arm_spe_pmu_buf_get_fault_act(handle);
			if (act == SPE_PMU_BUF_FAULT_ACT_SPURIOUS)
				arm_spe_perf_aux_output_end(handle);
			else
				write_sysreg_s(0, SYS_PMBSR_EL1);
		}

		/*
		 * This may also contain ECOUNT, but nobody else should
		 * be looking at period_left, since we forbid frequency
		 * based sampling.
		 */
		local64_set(&hwc->period_left, read_sysreg_s(SYS_PMSICR_EL1));
		hwc->state |= PERF_HES_UPTODATE;
	}

	hwc->state |= PERF_HES_STOPPED;
}