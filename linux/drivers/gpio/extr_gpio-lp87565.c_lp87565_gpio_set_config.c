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
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  LP87565_GOIO1_OD ; 
 int /*<<< orphan*/  LP87565_REG_GPIO_CONFIG ; 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 129 
#define  PIN_CONFIG_DRIVE_PUSH_PULL 128 
 int /*<<< orphan*/  __ffs (int /*<<< orphan*/ ) ; 
 struct lp87565_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int pinconf_to_config_param (unsigned long) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lp87565_gpio_set_config(struct gpio_chip *gc, unsigned int offset,
				   unsigned long config)
{
	struct lp87565_gpio *gpio = gpiochip_get_data(gc);

	switch (pinconf_to_config_param(config)) {
	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
		return regmap_update_bits(gpio->map,
					  LP87565_REG_GPIO_CONFIG,
					  BIT(offset +
					      __ffs(LP87565_GOIO1_OD)),
					  BIT(offset +
					      __ffs(LP87565_GOIO1_OD)));
	case PIN_CONFIG_DRIVE_PUSH_PULL:
		return regmap_update_bits(gpio->map,
					  LP87565_REG_GPIO_CONFIG,
					  BIT(offset +
					      __ffs(LP87565_GOIO1_OD)), 0);
	default:
		return -ENOTSUPP;
	}
}