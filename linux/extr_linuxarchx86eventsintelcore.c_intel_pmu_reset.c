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
struct debug_store {int /*<<< orphan*/  bts_buffer_base; int /*<<< orphan*/  bts_index; } ;
struct TYPE_4__ {int /*<<< orphan*/  ds; } ;
struct TYPE_3__ {int num_counters; int num_counters_fixed; int version; scalar_t__ lbr_nr; } ;

/* Variables and functions */
 int DEBUGCTLMSR_FREEZE_LBRS_ON_PMI ; 
 int DEBUGCTLMSR_LBR ; 
 scalar_t__ MSR_ARCH_PERFMON_FIXED_CTR0 ; 
 int /*<<< orphan*/  MSR_CORE_PERF_GLOBAL_CTRL ; 
 struct debug_store* __this_cpu_read (int /*<<< orphan*/ ) ; 
 TYPE_2__ cpu_hw_events ; 
 int get_debugctlmsr () ; 
 int /*<<< orphan*/  intel_pmu_ack_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_pmu_get_status () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  update_debugctlmsr (int) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl_safe (scalar_t__,unsigned long long) ; 
 TYPE_1__ x86_pmu ; 
 scalar_t__ x86_pmu_config_addr (int) ; 
 scalar_t__ x86_pmu_event_addr (int) ; 

__attribute__((used)) static void intel_pmu_reset(void)
{
	struct debug_store *ds = __this_cpu_read(cpu_hw_events.ds);
	unsigned long flags;
	int idx;

	if (!x86_pmu.num_counters)
		return;

	local_irq_save(flags);

	pr_info("clearing PMU state on CPU#%d\n", smp_processor_id());

	for (idx = 0; idx < x86_pmu.num_counters; idx++) {
		wrmsrl_safe(x86_pmu_config_addr(idx), 0ull);
		wrmsrl_safe(x86_pmu_event_addr(idx),  0ull);
	}
	for (idx = 0; idx < x86_pmu.num_counters_fixed; idx++)
		wrmsrl_safe(MSR_ARCH_PERFMON_FIXED_CTR0 + idx, 0ull);

	if (ds)
		ds->bts_index = ds->bts_buffer_base;

	/* Ack all overflows and disable fixed counters */
	if (x86_pmu.version >= 2) {
		intel_pmu_ack_status(intel_pmu_get_status());
		wrmsrl(MSR_CORE_PERF_GLOBAL_CTRL, 0);
	}

	/* Reset LBRs and LBR freezing */
	if (x86_pmu.lbr_nr) {
		update_debugctlmsr(get_debugctlmsr() &
			~(DEBUGCTLMSR_FREEZE_LBRS_ON_PMI|DEBUGCTLMSR_LBR));
	}

	local_irq_restore(flags);
}