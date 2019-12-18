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
struct sx150x_pinctrl {TYPE_1__* data; int /*<<< orphan*/  regmap; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg_data; } ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 int EINVAL ; 
 struct sx150x_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 scalar_t__ sx150x_pin_is_oscio (struct sx150x_pinctrl*,unsigned int) ; 

__attribute__((used)) static int sx150x_gpio_get(struct gpio_chip *chip, unsigned int offset)
{
	struct sx150x_pinctrl *pctl = gpiochip_get_data(chip);
	unsigned int value;
	int ret;

	if (sx150x_pin_is_oscio(pctl, offset))
		return -EINVAL;

	ret = regmap_read(pctl->regmap, pctl->data->reg_data, &value);
	if (ret < 0)
		return ret;

	return !!(value & BIT(offset));
}