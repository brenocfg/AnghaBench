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
struct stmfx_pinctrl {int /*<<< orphan*/  lock; } ;
struct irq_data {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct stmfx_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stmfx_pinctrl_irq_bus_lock(struct irq_data *data)
{
	struct gpio_chip *gpio_chip = irq_data_get_irq_chip_data(data);
	struct stmfx_pinctrl *pctl = gpiochip_get_data(gpio_chip);

	mutex_lock(&pctl->lock);
}