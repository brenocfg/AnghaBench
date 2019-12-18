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
struct gpio_chip {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int gpiochip_reqres_irq (struct gpio_chip*,int /*<<< orphan*/ ) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zynq_gpio_irq_reqres(struct irq_data *d)
{
	struct gpio_chip *chip = irq_data_get_irq_chip_data(d);
	int ret;

	ret = pm_runtime_get_sync(chip->parent);
	if (ret < 0)
		return ret;

	return gpiochip_reqres_irq(chip, d->hwirq);
}