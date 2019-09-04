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
struct gpio_bank {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int irq_set_irq_wake (int /*<<< orphan*/ ,unsigned int) ; 
 struct gpio_bank* omap_irq_data_get_bank (struct irq_data*) ; 

__attribute__((used)) static int omap_gpio_wake_enable(struct irq_data *d, unsigned int enable)
{
	struct gpio_bank *bank = omap_irq_data_get_bank(d);

	return irq_set_irq_wake(bank->irq, enable);
}