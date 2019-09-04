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

/* Variables and functions */

__attribute__((used)) static void
bcm2836_arm_irqchip_smp_init(void)
{
#ifdef CONFIG_SMP
	/* Unmask IPIs to the boot CPU. */
	cpuhp_setup_state(CPUHP_AP_IRQ_BCM2836_STARTING,
			  "irqchip/bcm2836:starting", bcm2836_cpu_starting,
			  bcm2836_cpu_dying);

	set_smp_cross_call(bcm2836_arm_irqchip_send_ipi);
#endif
}