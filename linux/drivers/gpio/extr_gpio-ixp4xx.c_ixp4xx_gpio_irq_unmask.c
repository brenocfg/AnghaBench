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
struct ixp4xx_gpio {int irq_edge; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 struct ixp4xx_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  irq_chip_unmask_parent (struct irq_data*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  ixp4xx_gpio_irq_ack (struct irq_data*) ; 

__attribute__((used)) static void ixp4xx_gpio_irq_unmask(struct irq_data *d)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct ixp4xx_gpio *g = gpiochip_get_data(gc);

	/* ACK when unmasking if not edge-triggered */
	if (!(g->irq_edge & BIT(d->hwirq)))
		ixp4xx_gpio_irq_ack(d);

	irq_chip_unmask_parent(d);
}