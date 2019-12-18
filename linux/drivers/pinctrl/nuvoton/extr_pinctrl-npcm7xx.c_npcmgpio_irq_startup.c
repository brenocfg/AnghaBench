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
struct irq_data {unsigned int hwirq; int /*<<< orphan*/  irq; TYPE_1__* chip; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  npcmgpio_direction_input (struct gpio_chip*,unsigned int) ; 
 int /*<<< orphan*/  npcmgpio_irq_ack (struct irq_data*) ; 
 int /*<<< orphan*/  npcmgpio_irq_unmask (struct irq_data*) ; 

__attribute__((used)) static unsigned int npcmgpio_irq_startup(struct irq_data *d)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	unsigned int gpio = d->hwirq;

	/* active-high, input, clear interrupt, enable interrupt */
	dev_dbg(d->chip->parent_device, "startup: %u.%u\n", gpio, d->irq);
	npcmgpio_direction_input(gc, gpio);
	npcmgpio_irq_ack(d);
	npcmgpio_irq_unmask(d);

	return 0;
}