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
 int /*<<< orphan*/  GIC_LOCAL_INT_PERFCTR ; 
 int /*<<< orphan*/  GIC_LOCAL_TO_HWIRQ (int /*<<< orphan*/ ) ; 
 int MIPS_CPU_IRQ_BASE ; 
 scalar_t__ cp0_perfcount_irq ; 
 int /*<<< orphan*/  gic_irq_domain ; 
 int /*<<< orphan*/  gic_local_irq_is_routable (int /*<<< orphan*/ ) ; 
 int irq_create_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int gic_get_c0_perfcount_int(void)
{
	if (!gic_local_irq_is_routable(GIC_LOCAL_INT_PERFCTR)) {
		/* Is the performance counter shared with the timer? */
		if (cp0_perfcount_irq < 0)
			return -1;
		return MIPS_CPU_IRQ_BASE + cp0_perfcount_irq;
	}
	return irq_create_mapping(gic_irq_domain,
				  GIC_LOCAL_TO_HWIRQ(GIC_LOCAL_INT_PERFCTR));
}