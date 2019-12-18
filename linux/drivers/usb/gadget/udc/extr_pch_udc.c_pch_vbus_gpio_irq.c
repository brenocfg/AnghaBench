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
struct TYPE_2__ {int /*<<< orphan*/  irq_work_fall; int /*<<< orphan*/  irq_work_rise; int /*<<< orphan*/  intr; int /*<<< orphan*/  port; } ;
struct pch_udc_dev {TYPE_1__ vbus_gpio; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ pch_vbus_gpio_get_value (struct pch_udc_dev*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t pch_vbus_gpio_irq(int irq, void *data)
{
	struct pch_udc_dev *dev = (struct pch_udc_dev *)data;

	if (!dev->vbus_gpio.port || !dev->vbus_gpio.intr)
		return IRQ_NONE;

	if (pch_vbus_gpio_get_value(dev))
		schedule_work(&dev->vbus_gpio.irq_work_rise);
	else
		schedule_work(&dev->vbus_gpio.irq_work_fall);

	return IRQ_HANDLED;
}