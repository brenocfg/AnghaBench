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
struct wcove_gpio {int update; int /*<<< orphan*/  buslock; } ;
struct irq_data {int hwirq; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int UPDATE_IRQ_MASK ; 
 int UPDATE_IRQ_TYPE ; 
 struct wcove_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcove_update_irq_ctrl (struct wcove_gpio*,int) ; 
 int /*<<< orphan*/  wcove_update_irq_mask (struct wcove_gpio*,int) ; 

__attribute__((used)) static void wcove_bus_sync_unlock(struct irq_data *data)
{
	struct gpio_chip *chip = irq_data_get_irq_chip_data(data);
	struct wcove_gpio *wg = gpiochip_get_data(chip);
	int gpio = data->hwirq;

	if (wg->update & UPDATE_IRQ_TYPE)
		wcove_update_irq_ctrl(wg, gpio);
	if (wg->update & UPDATE_IRQ_MASK)
		wcove_update_irq_mask(wg, gpio);
	wg->update = 0;

	mutex_unlock(&wg->buslock);
}