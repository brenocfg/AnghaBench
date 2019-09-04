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
typedef  int /*<<< orphan*/  u32 ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 unsigned long PIN_CONFIG_BIAS_DISABLE ; 
 unsigned long PIN_CONFIG_BIAS_PULL_DOWN ; 
 unsigned long PIN_CONFIG_DRIVE_OPEN_DRAIN ; 
 unsigned long PIN_CONFIG_DRIVE_OPEN_SOURCE ; 
 unsigned long PIN_CONFIG_DRIVE_STRENGTH ; 
 unsigned long PIN_CONFIG_INPUT_DEBOUNCE ; 
 unsigned long PIN_CONFIG_PERSIST_STATE ; 
 int aspeed_gpio_reset_tolerance (struct gpio_chip*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinconf_to_config_argument (unsigned long) ; 
 unsigned long pinconf_to_config_param (unsigned long) ; 
 int pinctrl_gpio_set_config (unsigned int,unsigned long) ; 
 int set_debounce (struct gpio_chip*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aspeed_gpio_set_config(struct gpio_chip *chip, unsigned int offset,
				  unsigned long config)
{
	unsigned long param = pinconf_to_config_param(config);
	u32 arg = pinconf_to_config_argument(config);

	if (param == PIN_CONFIG_INPUT_DEBOUNCE)
		return set_debounce(chip, offset, arg);
	else if (param == PIN_CONFIG_BIAS_DISABLE ||
			param == PIN_CONFIG_BIAS_PULL_DOWN ||
			param == PIN_CONFIG_DRIVE_STRENGTH)
		return pinctrl_gpio_set_config(offset, config);
	else if (param == PIN_CONFIG_DRIVE_OPEN_DRAIN ||
			param == PIN_CONFIG_DRIVE_OPEN_SOURCE)
		/* Return -ENOTSUPP to trigger emulation, as per datasheet */
		return -ENOTSUPP;
	else if (param == PIN_CONFIG_PERSIST_STATE)
		return aspeed_gpio_reset_tolerance(chip, offset, arg);

	return -ENOTSUPP;
}