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
struct lp873x_gpio {TYPE_1__* lp873; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 unsigned int BITS_PER_GPO ; 
 int ENOTSUPP ; 
 unsigned int LP873X_GPO_CTRL_OD ; 
 int /*<<< orphan*/  LP873X_REG_GPO_CTRL ; 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 129 
#define  PIN_CONFIG_DRIVE_PUSH_PULL 128 
 struct lp873x_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int pinconf_to_config_param (unsigned long) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lp873x_gpio_set_config(struct gpio_chip *gc, unsigned offset,
				  unsigned long config)
{
	struct lp873x_gpio *gpio = gpiochip_get_data(gc);

	switch (pinconf_to_config_param(config)) {
	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
		return regmap_update_bits(gpio->lp873->regmap,
					  LP873X_REG_GPO_CTRL,
					  BIT(offset * BITS_PER_GPO +
					  LP873X_GPO_CTRL_OD),
					  BIT(offset * BITS_PER_GPO +
					  LP873X_GPO_CTRL_OD));

	case PIN_CONFIG_DRIVE_PUSH_PULL:
		return regmap_update_bits(gpio->lp873->regmap,
					  LP873X_REG_GPO_CTRL,
					  BIT(offset * BITS_PER_GPO +
					  LP873X_GPO_CTRL_OD), 0);
	default:
		return -ENOTSUPP;
	}
}