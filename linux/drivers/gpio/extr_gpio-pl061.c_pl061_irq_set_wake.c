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
struct pl061 {int /*<<< orphan*/  parent_irq; } ;
struct irq_data {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct pl061* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int irq_set_irq_wake (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int pl061_irq_set_wake(struct irq_data *d, unsigned int state)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct pl061 *pl061 = gpiochip_get_data(gc);

	return irq_set_irq_wake(pl061->parent_irq, state);
}