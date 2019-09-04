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
struct irq_data {scalar_t__ hwirq; } ;
struct TYPE_2__ {scalar_t__* enable; scalar_t__ base; scalar_t__ local_base; } ;

/* Variables and functions */
 scalar_t__ ARM_LOCAL_GPU_INT_ROUTING ; 
 size_t HWIRQ_BANK (scalar_t__) ; 
 unsigned int HWIRQ_BIT (scalar_t__) ; 
 scalar_t__ NUMBER_IRQS ; 
 scalar_t__ REG_FIQ_CONTROL ; 
 unsigned int REG_FIQ_ENABLE ; 
 unsigned int hwirq_to_fiq (scalar_t__) ; 
 TYPE_1__ intc ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 unsigned int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

__attribute__((used)) static void armctrl_unmask_irq(struct irq_data *d)
{
	if (d->hwirq >= NUMBER_IRQS) {
		if (num_online_cpus() > 1) {
			unsigned int data;

			if (!intc.local_base) {
				pr_err("FIQ is disabled due to missing arm_local_intc\n");
				return;
			}

			data = readl_relaxed(intc.local_base +
					     ARM_LOCAL_GPU_INT_ROUTING);

			data &= ~0xc;
			data |= (1 << 2);
			writel_relaxed(data,
				       intc.local_base +
				       ARM_LOCAL_GPU_INT_ROUTING);
		}

		writel_relaxed(REG_FIQ_ENABLE | hwirq_to_fiq(d->hwirq),
			       intc.base + REG_FIQ_CONTROL);
	} else {
		writel_relaxed(HWIRQ_BIT(d->hwirq),
			       intc.enable[HWIRQ_BANK(d->hwirq)]);
	}
}