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
struct TYPE_2__ {int cpu_start; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int nr_cpu_ids ; 
 TYPE_1__** paca_ptrs ; 
 int /*<<< orphan*/  smp_startup_cpu (int) ; 

__attribute__((used)) static int smp_pSeries_kick_cpu(int nr)
{
	if (nr < 0 || nr >= nr_cpu_ids)
		return -EINVAL;

	if (!smp_startup_cpu(nr))
		return -ENOENT;

	/*
	 * The processor is currently spinning, waiting for the
	 * cpu_start field to become non-zero After we set cpu_start,
	 * the processor will continue on to secondary_start
	 */
	paca_ptrs[nr]->cpu_start = 1;
#ifdef CONFIG_HOTPLUG_CPU
	set_preferred_offline_state(nr, CPU_STATE_ONLINE);

	if (get_cpu_current_state(nr) == CPU_STATE_INACTIVE) {
		long rc;
		unsigned long hcpuid;

		hcpuid = get_hard_smp_processor_id(nr);
		rc = plpar_hcall_norets(H_PROD, hcpuid);
		if (rc != H_SUCCESS)
			printk(KERN_ERR "Error: Prod to wake up processor %d "
						"Ret= %ld\n", nr, rc);
	}
#endif

	return 0;
}