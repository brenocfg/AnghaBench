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
struct solo_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  solo_gpio_config (struct solo_dev*) ; 

int solo_gpio_init(struct solo_dev *solo_dev)
{
#ifdef CONFIG_GPIOLIB
	int ret;
#endif

	solo_gpio_config(solo_dev);
#ifdef CONFIG_GPIOLIB
	solo_dev->gpio_dev.label = SOLO6X10_NAME"_gpio";
	solo_dev->gpio_dev.parent = &solo_dev->pdev->dev;
	solo_dev->gpio_dev.owner = THIS_MODULE;
	solo_dev->gpio_dev.base = -1;
	solo_dev->gpio_dev.ngpio = 24;
	solo_dev->gpio_dev.can_sleep = 0;

	solo_dev->gpio_dev.get_direction = solo_gpiochip_get_direction;
	solo_dev->gpio_dev.direction_input = solo_gpiochip_direction_input;
	solo_dev->gpio_dev.direction_output = solo_gpiochip_direction_output;
	solo_dev->gpio_dev.get = solo_gpiochip_get;
	solo_dev->gpio_dev.set = solo_gpiochip_set;

	ret = gpiochip_add_data(&solo_dev->gpio_dev, solo_dev);

	if (ret) {
		solo_dev->gpio_dev.label = NULL;
		return -1;
	}
#endif
	return 0;
}