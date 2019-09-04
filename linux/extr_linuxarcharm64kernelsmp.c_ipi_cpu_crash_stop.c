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
struct pt_regs {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void ipi_cpu_crash_stop(unsigned int cpu, struct pt_regs *regs)
{
#ifdef CONFIG_KEXEC_CORE
	crash_save_cpu(regs, cpu);

	atomic_dec(&waiting_for_crash_ipi);

	local_irq_disable();
	sdei_mask_local_cpu();

#ifdef CONFIG_HOTPLUG_CPU
	if (cpu_ops[cpu]->cpu_die)
		cpu_ops[cpu]->cpu_die(cpu);
#endif

	/* just in case */
	cpu_park_loop();
#endif
}