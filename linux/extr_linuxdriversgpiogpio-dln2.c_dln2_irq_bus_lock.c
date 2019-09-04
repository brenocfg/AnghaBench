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
struct gpio_chip {int dummy; } ;
struct dln2_gpio {int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 struct dln2_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dln2_irq_bus_lock(struct irq_data *irqd)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(irqd);
	struct dln2_gpio *dln2 = gpiochip_get_data(gc);

	mutex_lock(&dln2->irq_lock);
}