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
struct lp87565_gpio {int /*<<< orphan*/  map; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  LP87565_REG_GPIO_IN ; 
 struct lp87565_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int lp87565_gpio_get(struct gpio_chip *chip, unsigned int offset)
{
	struct lp87565_gpio *gpio = gpiochip_get_data(chip);
	int ret, val;

	ret = regmap_read(gpio->map, LP87565_REG_GPIO_IN, &val);
	if (ret < 0)
		return ret;

	return !!(val & BIT(offset));
}