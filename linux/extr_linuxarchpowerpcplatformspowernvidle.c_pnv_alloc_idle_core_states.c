#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct paca_struct {int dummy; } ;
struct TYPE_2__ {int* core_idle_state_ptr; int thread_mask; int /*<<< orphan*/  thread_idle_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int OPAL_PM_LOSE_FULL_CONTEXT ; 
 int /*<<< orphan*/  PNV_THREAD_RUNNING ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int cpu_nr_cores () ; 
 int cpu_to_node (int) ; 
 int deepest_stop_found ; 
 scalar_t__ default_stop_found ; 
 int* kmalloc_node (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ likely (int) ; 
 TYPE_1__** paca_ptrs ; 
 int pnv_deepest_stop_flag ; 
 int /*<<< orphan*/  pnv_deepest_stop_psscr_mask ; 
 int /*<<< orphan*/  pnv_deepest_stop_psscr_val ; 
 int /*<<< orphan*/  pnv_default_stop_mask ; 
 int /*<<< orphan*/  pnv_default_stop_val ; 
 int pnv_save_sprs_for_deep_states () ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int supported_cpuidle_states ; 
 int threads_per_core ; 
 int /*<<< orphan*/  update_subcore_sibling_mask () ; 

__attribute__((used)) static void pnv_alloc_idle_core_states(void)
{
	int i, j;
	int nr_cores = cpu_nr_cores();
	u32 *core_idle_state;

	/*
	 * core_idle_state - The lower 8 bits track the idle state of
	 * each thread of the core.
	 *
	 * The most significant bit is the lock bit.
	 *
	 * Initially all the bits corresponding to threads_per_core
	 * are set. They are cleared when the thread enters deep idle
	 * state like sleep and winkle/stop.
	 *
	 * Initially the lock bit is cleared.  The lock bit has 2
	 * purposes:
	 * 	a. While the first thread in the core waking up from
	 * 	   idle is restoring core state, it prevents other
	 * 	   threads in the core from switching to process
	 * 	   context.
	 * 	b. While the last thread in the core is saving the
	 *	   core state, it prevents a different thread from
	 *	   waking up.
	 */
	for (i = 0; i < nr_cores; i++) {
		int first_cpu = i * threads_per_core;
		int node = cpu_to_node(first_cpu);
		size_t paca_ptr_array_size;

		core_idle_state = kmalloc_node(sizeof(u32), GFP_KERNEL, node);
		*core_idle_state = (1 << threads_per_core) - 1;
		paca_ptr_array_size = (threads_per_core *
				       sizeof(struct paca_struct *));

		for (j = 0; j < threads_per_core; j++) {
			int cpu = first_cpu + j;

			paca_ptrs[cpu]->core_idle_state_ptr = core_idle_state;
			paca_ptrs[cpu]->thread_idle_state = PNV_THREAD_RUNNING;
			paca_ptrs[cpu]->thread_mask = 1 << j;
		}
	}

	update_subcore_sibling_mask();

	if (supported_cpuidle_states & OPAL_PM_LOSE_FULL_CONTEXT) {
		int rc = pnv_save_sprs_for_deep_states();

		if (likely(!rc))
			return;

		/*
		 * The stop-api is unable to restore hypervisor
		 * resources on wakeup from platform idle states which
		 * lose full context. So disable such states.
		 */
		supported_cpuidle_states &= ~OPAL_PM_LOSE_FULL_CONTEXT;
		pr_warn("cpuidle-powernv: Disabling idle states that lose full context\n");
		pr_warn("cpuidle-powernv: Idle power-savings, CPU-Hotplug affected\n");

		if (cpu_has_feature(CPU_FTR_ARCH_300) &&
		    (pnv_deepest_stop_flag & OPAL_PM_LOSE_FULL_CONTEXT)) {
			/*
			 * Use the default stop state for CPU-Hotplug
			 * if available.
			 */
			if (default_stop_found) {
				pnv_deepest_stop_psscr_val =
					pnv_default_stop_val;
				pnv_deepest_stop_psscr_mask =
					pnv_default_stop_mask;
				pr_warn("cpuidle-powernv: Offlined CPUs will stop with psscr = 0x%016llx\n",
					pnv_deepest_stop_psscr_val);
			} else { /* Fallback to snooze loop for CPU-Hotplug */
				deepest_stop_found = false;
				pr_warn("cpuidle-powernv: Offlined CPUs will busy wait\n");
			}
		}
	}
}