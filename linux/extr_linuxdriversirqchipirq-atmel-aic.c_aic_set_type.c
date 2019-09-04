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
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct irq_chip_generic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_AIC_SMR (int /*<<< orphan*/ ) ; 
 int aic_common_set_type (struct irq_data*,unsigned int,unsigned int*) ; 
 struct irq_chip_generic* irq_data_get_irq_chip_data (struct irq_data*) ; 
 unsigned int irq_reg_readl (struct irq_chip_generic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_reg_writel (struct irq_chip_generic*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aic_set_type(struct irq_data *d, unsigned type)
{
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	unsigned int smr;
	int ret;

	smr = irq_reg_readl(gc, AT91_AIC_SMR(d->hwirq));
	ret = aic_common_set_type(d, type, &smr);
	if (ret)
		return ret;

	irq_reg_writel(gc, smr, AT91_AIC_SMR(d->hwirq));

	return 0;
}