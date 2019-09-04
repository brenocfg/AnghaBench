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
struct gpio_fan_data {int /*<<< orphan*/  alarm_work; int /*<<< orphan*/  alarm_gpio; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  IRQ_TYPE_EDGE_BOTH ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct gpio_fan_data*) ; 
 int /*<<< orphan*/  fan_alarm_irq_handler ; 
 int /*<<< orphan*/  fan_alarm_notify ; 
 int gpiod_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_irq_type (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fan_alarm_init(struct gpio_fan_data *fan_data)
{
	int alarm_irq;
	struct device *dev = fan_data->dev;

	/*
	 * If the alarm GPIO don't support interrupts, just leave
	 * without initializing the fail notification support.
	 */
	alarm_irq = gpiod_to_irq(fan_data->alarm_gpio);
	if (alarm_irq <= 0)
		return 0;

	INIT_WORK(&fan_data->alarm_work, fan_alarm_notify);
	irq_set_irq_type(alarm_irq, IRQ_TYPE_EDGE_BOTH);
	return devm_request_irq(dev, alarm_irq, fan_alarm_irq_handler,
				IRQF_SHARED, "GPIO fan alarm", fan_data);
}