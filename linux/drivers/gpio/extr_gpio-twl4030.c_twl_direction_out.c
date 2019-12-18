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
struct gpio_twl4030_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  direction; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 unsigned int TWL4030_GPIO_MAX ; 
 struct gpio_twl4030_priv* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int twl4030_set_gpio_direction (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl_set (struct gpio_chip*,unsigned int,int) ; 

__attribute__((used)) static int twl_direction_out(struct gpio_chip *chip, unsigned offset, int value)
{
	struct gpio_twl4030_priv *priv = gpiochip_get_data(chip);
	int ret = 0;

	mutex_lock(&priv->mutex);
	if (offset < TWL4030_GPIO_MAX) {
		ret = twl4030_set_gpio_direction(offset, 0);
		if (ret) {
			mutex_unlock(&priv->mutex);
			return ret;
		}
	}

	/*
	 *  LED gpios i.e. offset >= TWL4030_GPIO_MAX are always output
	 */

	priv->direction |= BIT(offset);
	mutex_unlock(&priv->mutex);

	twl_set(chip, offset, value);

	return ret;
}