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
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int gpio_to_pin (struct pinctrl_gpio_range*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pinctrl_get_device_gpio_range (unsigned int,struct pinctrl_dev**,struct pinctrl_gpio_range**) ; 
 int pinmux_can_be_used_for_gpio (struct pinctrl_dev*,int) ; 

bool pinctrl_gpio_can_use_line(unsigned gpio)
{
	struct pinctrl_dev *pctldev;
	struct pinctrl_gpio_range *range;
	bool result;
	int pin;

	/*
	 * Try to obtain GPIO range, if it fails
	 * we're probably dealing with GPIO driver
	 * without a backing pin controller - bail out.
	 */
	if (pinctrl_get_device_gpio_range(gpio, &pctldev, &range))
		return true;

	mutex_lock(&pctldev->mutex);

	/* Convert to the pin controllers number space */
	pin = gpio_to_pin(range, gpio);

	result = pinmux_can_be_used_for_gpio(pctldev, pin);

	mutex_unlock(&pctldev->mutex);

	return result;
}