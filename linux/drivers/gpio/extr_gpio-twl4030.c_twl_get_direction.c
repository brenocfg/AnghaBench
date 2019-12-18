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
struct gpio_twl4030_priv {int /*<<< orphan*/  mutex; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned int TWL4030_GPIO_MAX ; 
 struct gpio_twl4030_priv* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int twl4030_get_gpio_direction (unsigned int) ; 

__attribute__((used)) static int twl_get_direction(struct gpio_chip *chip, unsigned offset)
{
	struct gpio_twl4030_priv *priv = gpiochip_get_data(chip);
	/*
	 * Default 0 = output
	 * LED GPIOs >= TWL4030_GPIO_MAX are always output
	 */
	int ret = 0;

	mutex_lock(&priv->mutex);
	if (offset < TWL4030_GPIO_MAX) {
		ret = twl4030_get_gpio_direction(offset);
		if (ret) {
			mutex_unlock(&priv->mutex);
			return ret;
		}
	}
	mutex_unlock(&priv->mutex);

	return ret;
}