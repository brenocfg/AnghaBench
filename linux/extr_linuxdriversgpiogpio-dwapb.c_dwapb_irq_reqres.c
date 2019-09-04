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
struct irq_chip_generic {struct dwapb_gpio* private; } ;
struct gpio_chip {int dummy; } ;
struct dwapb_gpio {int /*<<< orphan*/  dev; TYPE_1__* ports; } ;
struct TYPE_2__ {struct gpio_chip gc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int gpiochip_lock_as_irq (struct gpio_chip*,int /*<<< orphan*/ ) ; 
 struct irq_chip_generic* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_to_hwirq (struct irq_data*) ; 

__attribute__((used)) static int dwapb_irq_reqres(struct irq_data *d)
{
	struct irq_chip_generic *igc = irq_data_get_irq_chip_data(d);
	struct dwapb_gpio *gpio = igc->private;
	struct gpio_chip *gc = &gpio->ports[0].gc;
	int ret;

	ret = gpiochip_lock_as_irq(gc, irqd_to_hwirq(d));
	if (ret) {
		dev_err(gpio->dev, "unable to lock HW IRQ %lu for IRQ\n",
			irqd_to_hwirq(d));
		return ret;
	}
	return 0;
}