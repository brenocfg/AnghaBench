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
struct gpiod_data {unsigned int irq_flags; struct gpio_desc* desc; } ;
struct gpio_desc {int /*<<< orphan*/  flags; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_ACTIVE_LOW ; 
 unsigned int GPIO_IRQF_TRIGGER_FALLING ; 
 unsigned int GPIO_IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct gpiod_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  gpio_sysfs_free_irq (struct device*) ; 
 int gpio_sysfs_request_irq (struct device*,unsigned int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gpio_sysfs_set_active_low(struct device *dev, int value)
{
	struct gpiod_data	*data = dev_get_drvdata(dev);
	struct gpio_desc	*desc = data->desc;
	int			status = 0;
	unsigned int		flags = data->irq_flags;

	if (!!test_bit(FLAG_ACTIVE_LOW, &desc->flags) == !!value)
		return 0;

	if (value)
		set_bit(FLAG_ACTIVE_LOW, &desc->flags);
	else
		clear_bit(FLAG_ACTIVE_LOW, &desc->flags);

	/* reconfigure poll(2) support if enabled on one edge only */
	if (flags == GPIO_IRQF_TRIGGER_FALLING ||
					flags == GPIO_IRQF_TRIGGER_RISING) {
		gpio_sysfs_free_irq(dev);
		status = gpio_sysfs_request_irq(dev, flags);
	}

	return status;
}