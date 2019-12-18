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
struct max77620_gpio {int /*<<< orphan*/  rmap; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  GPIO_REG_ADDR (unsigned int) ; 
 int /*<<< orphan*/  MAX77620_CNFG_GPIO_DRV_MASK ; 
 int /*<<< orphan*/  MAX77620_CNFG_GPIO_DRV_OPENDRAIN ; 
 int /*<<< orphan*/  MAX77620_CNFG_GPIO_DRV_PUSHPULL ; 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 130 
#define  PIN_CONFIG_DRIVE_PUSH_PULL 129 
#define  PIN_CONFIG_INPUT_DEBOUNCE 128 
 struct max77620_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int max77620_gpio_set_debounce (struct max77620_gpio*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinconf_to_config_argument (unsigned long) ; 
 int pinconf_to_config_param (unsigned long) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max77620_gpio_set_config(struct gpio_chip *gc, unsigned int offset,
				    unsigned long config)
{
	struct max77620_gpio *mgpio = gpiochip_get_data(gc);

	switch (pinconf_to_config_param(config)) {
	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
		return regmap_update_bits(mgpio->rmap, GPIO_REG_ADDR(offset),
					  MAX77620_CNFG_GPIO_DRV_MASK,
					  MAX77620_CNFG_GPIO_DRV_OPENDRAIN);
	case PIN_CONFIG_DRIVE_PUSH_PULL:
		return regmap_update_bits(mgpio->rmap, GPIO_REG_ADDR(offset),
					  MAX77620_CNFG_GPIO_DRV_MASK,
					  MAX77620_CNFG_GPIO_DRV_PUSHPULL);
	case PIN_CONFIG_INPUT_DEBOUNCE:
		return max77620_gpio_set_debounce(mgpio, offset,
			pinconf_to_config_argument(config));
	default:
		break;
	}

	return -ENOTSUPP;
}