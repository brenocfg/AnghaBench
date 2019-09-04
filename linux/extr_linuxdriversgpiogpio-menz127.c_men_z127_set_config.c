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
struct gpio_chip {int dummy; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 130 
#define  PIN_CONFIG_DRIVE_PUSH_PULL 129 
#define  PIN_CONFIG_INPUT_DEBOUNCE 128 
 int men_z127_debounce (struct gpio_chip*,unsigned int,int /*<<< orphan*/ ) ; 
 int men_z127_set_single_ended (struct gpio_chip*,unsigned int,int) ; 
 int /*<<< orphan*/  pinconf_to_config_argument (unsigned long) ; 
 int pinconf_to_config_param (unsigned long) ; 

__attribute__((used)) static int men_z127_set_config(struct gpio_chip *gc, unsigned offset,
			       unsigned long config)
{
	enum pin_config_param param = pinconf_to_config_param(config);

	switch (param) {
	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
	case PIN_CONFIG_DRIVE_PUSH_PULL:
		return men_z127_set_single_ended(gc, offset, param);

	case PIN_CONFIG_INPUT_DEBOUNCE:
		return men_z127_debounce(gc, offset,
			pinconf_to_config_argument(config));

	default:
		break;
	}

	return -ENOTSUPP;
}