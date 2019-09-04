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
struct TYPE_3__ {int /*<<< orphan*/  config; } ;
struct perf_event {TYPE_1__ hw; } ;
struct cpu_hw_events {int intel_ctrl_guest_mask; struct perf_event** events; int /*<<< orphan*/  active_mask; } ;
struct TYPE_4__ {int intel_ctrl; } ;

/* Variables and functions */
 size_t INTEL_PMC_IDX_FIXED_BTS ; 
 int /*<<< orphan*/  MSR_CORE_PERF_GLOBAL_CTRL ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  intel_pmu_enable_bts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_pmu_lbr_enable_all (int) ; 
 int /*<<< orphan*/  intel_pmu_pebs_enable_all () ; 
 scalar_t__ test_bit (size_t,int /*<<< orphan*/ ) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 
 TYPE_2__ x86_pmu ; 

__attribute__((used)) static void __intel_pmu_enable_all(int added, bool pmi)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	intel_pmu_pebs_enable_all();
	intel_pmu_lbr_enable_all(pmi);
	wrmsrl(MSR_CORE_PERF_GLOBAL_CTRL,
			x86_pmu.intel_ctrl & ~cpuc->intel_ctrl_guest_mask);

	if (test_bit(INTEL_PMC_IDX_FIXED_BTS, cpuc->active_mask)) {
		struct perf_event *event =
			cpuc->events[INTEL_PMC_IDX_FIXED_BTS];

		if (WARN_ON_ONCE(!event))
			return;

		intel_pmu_enable_bts(event->hw.config);
	}
}