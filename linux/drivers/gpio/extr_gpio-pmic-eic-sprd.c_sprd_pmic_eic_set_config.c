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
 unsigned long PIN_CONFIG_INPUT_DEBOUNCE ; 
 int /*<<< orphan*/  pinconf_to_config_argument (unsigned long) ; 
 unsigned long pinconf_to_config_param (unsigned long) ; 
 int sprd_pmic_eic_set_debounce (struct gpio_chip*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sprd_pmic_eic_set_config(struct gpio_chip *chip, unsigned int offset,
				    unsigned long config)
{
	unsigned long param = pinconf_to_config_param(config);
	u32 arg = pinconf_to_config_argument(config);

	if (param == PIN_CONFIG_INPUT_DEBOUNCE)
		return sprd_pmic_eic_set_debounce(chip, offset, arg);

	return -ENOTSUPP;
}