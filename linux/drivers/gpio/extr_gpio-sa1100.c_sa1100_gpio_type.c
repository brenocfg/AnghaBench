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
struct sa1100_gpio_chip {unsigned int irqrising; unsigned int irqfalling; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_PROBE ; 
 struct sa1100_gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  sa1100_update_edge_regs (struct sa1100_gpio_chip*) ; 

__attribute__((used)) static int sa1100_gpio_type(struct irq_data *d, unsigned int type)
{
	struct sa1100_gpio_chip *sgc = irq_data_get_irq_chip_data(d);
	unsigned int mask = BIT(d->hwirq);

	if (type == IRQ_TYPE_PROBE) {
		if ((sgc->irqrising | sgc->irqfalling) & mask)
			return 0;
		type = IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING;
	}

	if (type & IRQ_TYPE_EDGE_RISING)
		sgc->irqrising |= mask;
	else
		sgc->irqrising &= ~mask;
	if (type & IRQ_TYPE_EDGE_FALLING)
		sgc->irqfalling |= mask;
	else
		sgc->irqfalling &= ~mask;

	sa1100_update_edge_regs(sgc);

	return 0;
}