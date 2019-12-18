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
struct max77650_gpio_chip {int /*<<< orphan*/  map; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  MAX77650_GPIO_DEBOUNCE ; 
 int /*<<< orphan*/  MAX77650_GPIO_DEBOUNCE_MASK ; 
 int /*<<< orphan*/  MAX77650_GPIO_DRV_MASK ; 
 int /*<<< orphan*/  MAX77650_GPIO_DRV_OPEN_DRAIN ; 
 int /*<<< orphan*/  MAX77650_GPIO_DRV_PUSH_PULL ; 
 int /*<<< orphan*/  MAX77650_REG_CNFG_GPIO ; 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 130 
#define  PIN_CONFIG_DRIVE_PUSH_PULL 129 
#define  PIN_CONFIG_INPUT_DEBOUNCE 128 
 struct max77650_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int pinconf_to_config_param (unsigned long) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max77650_gpio_set_config(struct gpio_chip *gc,
				    unsigned int offset, unsigned long cfg)
{
	struct max77650_gpio_chip *chip = gpiochip_get_data(gc);

	switch (pinconf_to_config_param(cfg)) {
	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
		return regmap_update_bits(chip->map,
					  MAX77650_REG_CNFG_GPIO,
					  MAX77650_GPIO_DRV_MASK,
					  MAX77650_GPIO_DRV_OPEN_DRAIN);
	case PIN_CONFIG_DRIVE_PUSH_PULL:
		return regmap_update_bits(chip->map,
					  MAX77650_REG_CNFG_GPIO,
					  MAX77650_GPIO_DRV_MASK,
					  MAX77650_GPIO_DRV_PUSH_PULL);
	case PIN_CONFIG_INPUT_DEBOUNCE:
		return regmap_update_bits(chip->map,
					  MAX77650_REG_CNFG_GPIO,
					  MAX77650_GPIO_DEBOUNCE_MASK,
					  MAX77650_GPIO_DEBOUNCE);
	default:
		return -ENOTSUPP;
	}
}