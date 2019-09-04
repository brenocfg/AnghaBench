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
struct ltc4306 {int /*<<< orphan*/  regmap; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  LTC_REG_MODE ; 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 129 
#define  PIN_CONFIG_DRIVE_PUSH_PULL 128 
 struct ltc4306* gpiochip_get_data (struct gpio_chip*) ; 
 int pinconf_to_config_param (unsigned long) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int ltc4306_gpio_set_config(struct gpio_chip *chip,
				   unsigned int offset, unsigned long config)
{
	struct ltc4306 *data = gpiochip_get_data(chip);
	unsigned int val;

	switch (pinconf_to_config_param(config)) {
	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
		val = 0;
		break;
	case PIN_CONFIG_DRIVE_PUSH_PULL:
		val = BIT(4 - offset);
		break;
	default:
		return -ENOTSUPP;
	}

	return regmap_update_bits(data->regmap, LTC_REG_MODE,
				  BIT(4 - offset), val);
}