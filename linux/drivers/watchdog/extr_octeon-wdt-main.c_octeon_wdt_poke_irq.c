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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_PP_POKEX (unsigned int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int cpu2core (int) ; 
 int cpu_to_node (int) ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_write_csr_node (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 scalar_t__ do_countdown ; 
 int /*<<< orphan*/  irq_enabled_cpus ; 
 scalar_t__* per_cpu_countdown ; 
 int raw_smp_processor_id () ; 

__attribute__((used)) static irqreturn_t octeon_wdt_poke_irq(int cpl, void *dev_id)
{
	int cpu = raw_smp_processor_id();
	unsigned int core = cpu2core(cpu);
	int node = cpu_to_node(cpu);

	if (do_countdown) {
		if (per_cpu_countdown[cpu] > 0) {
			/* We're alive, poke the watchdog */
			cvmx_write_csr_node(node, CVMX_CIU_PP_POKEX(core), 1);
			per_cpu_countdown[cpu]--;
		} else {
			/* Bad news, you are about to reboot. */
			disable_irq_nosync(cpl);
			cpumask_clear_cpu(cpu, &irq_enabled_cpus);
		}
	} else {
		/* Not open, just ping away... */
		cvmx_write_csr_node(node, CVMX_CIU_PP_POKEX(core), 1);
	}
	return IRQ_HANDLED;
}