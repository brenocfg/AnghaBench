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
struct irq_data {int dummy; } ;
struct cplds {unsigned int irq_mask; scalar_t__ base; } ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 scalar_t__ FPGA_IRQ_MASK_EN ; 
 struct cplds* irq_data_get_irq_chip_data (struct irq_data*) ; 
 unsigned int irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void cplds_irq_mask(struct irq_data *d)
{
	struct cplds *fpga = irq_data_get_irq_chip_data(d);
	unsigned int cplds_irq = irqd_to_hwirq(d);
	unsigned int bit = BIT(cplds_irq);

	fpga->irq_mask &= ~bit;
	writel(fpga->irq_mask, fpga->base + FPGA_IRQ_MASK_EN);
}