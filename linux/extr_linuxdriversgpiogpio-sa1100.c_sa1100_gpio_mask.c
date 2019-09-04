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
struct sa1100_gpio_chip {unsigned int irqmask; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 struct sa1100_gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  sa1100_update_edge_regs (struct sa1100_gpio_chip*) ; 

__attribute__((used)) static void sa1100_gpio_mask(struct irq_data *d)
{
	struct sa1100_gpio_chip *sgc = irq_data_get_irq_chip_data(d);
	unsigned int mask = BIT(d->hwirq);

	sgc->irqmask &= ~mask;

	sa1100_update_edge_regs(sgc);
}