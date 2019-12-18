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
struct TYPE_2__ {int /*<<< orphan*/  reg_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int __sx150x_gpio_set (struct sx150x_pinctrl*,unsigned int,int) ; 
 struct sx150x_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sx150x_gpio_oscio_set (struct sx150x_pinctrl*,int) ; 
 scalar_t__ sx150x_pin_is_oscio (struct sx150x_pinctrl*,unsigned int) ; 

__attribute__((used)) static int sx150x_gpio_direction_output(struct gpio_chip *chip,
					unsigned int offset, int value)
{
	struct sx150x_pinctrl *pctl = gpiochip_get_data(chip);
	int ret;

	if (sx150x_pin_is_oscio(pctl, offset))
		return sx150x_gpio_oscio_set(pctl, value);

	ret = __sx150x_gpio_set(pctl, offset, value);
	if (ret < 0)
		return ret;

	return regmap_write_bits(pctl->regmap,
				 pctl->data->reg_dir,
				 BIT(offset), 0);
}