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
struct irq_data {int dummy; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct dln2_gpio {unsigned int* irq_type; int /*<<< orphan*/  irq_lock; TYPE_1__ gpio; int /*<<< orphan*/  enabled_irqs; int /*<<< orphan*/  unmasked_irqs; } ;

/* Variables and functions */
 unsigned int DLN2_GPIO_EVENT_MASK ; 
 unsigned int DLN2_GPIO_EVENT_NONE ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dln2_gpio_set_event_cfg (struct dln2_gpio*,int,unsigned int,int /*<<< orphan*/ ) ; 
 struct dln2_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dln2_irq_bus_unlock(struct irq_data *irqd)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(irqd);
	struct dln2_gpio *dln2 = gpiochip_get_data(gc);
	int pin = irqd_to_hwirq(irqd);
	int enabled, unmasked;
	unsigned type;
	int ret;

	enabled = test_bit(pin, dln2->enabled_irqs);
	unmasked = test_bit(pin, dln2->unmasked_irqs);

	if (enabled != unmasked) {
		if (unmasked) {
			type = dln2->irq_type[pin] & DLN2_GPIO_EVENT_MASK;
			set_bit(pin, dln2->enabled_irqs);
		} else {
			type = DLN2_GPIO_EVENT_NONE;
			clear_bit(pin, dln2->enabled_irqs);
		}

		ret = dln2_gpio_set_event_cfg(dln2, pin, type, 0);
		if (ret)
			dev_err(dln2->gpio.parent, "failed to set event\n");
	}

	mutex_unlock(&dln2->irq_lock);
}