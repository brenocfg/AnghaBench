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
struct wm8994_gpio {struct wm8994* wm8994; } ;
struct wm8994 {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 129 
#define  PIN_CONFIG_DRIVE_PUSH_PULL 128 
 int /*<<< orphan*/  WM8994_GPIO_1 ; 
 int /*<<< orphan*/  WM8994_GPN_OP_CFG ; 
 int /*<<< orphan*/  WM8994_GPN_OP_CFG_MASK ; 
 struct wm8994_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int pinconf_to_config_param (unsigned long) ; 
 int wm8994_set_bits (struct wm8994*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8994_gpio_set_config(struct gpio_chip *chip, unsigned int offset,
				  unsigned long config)
{
	struct wm8994_gpio *wm8994_gpio = gpiochip_get_data(chip);
	struct wm8994 *wm8994 = wm8994_gpio->wm8994;

	switch (pinconf_to_config_param(config)) {
	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
		return wm8994_set_bits(wm8994, WM8994_GPIO_1 + offset,
				       WM8994_GPN_OP_CFG_MASK,
				       WM8994_GPN_OP_CFG);
	case PIN_CONFIG_DRIVE_PUSH_PULL:
		return wm8994_set_bits(wm8994, WM8994_GPIO_1 + offset,
				       WM8994_GPN_OP_CFG_MASK, 0);
	default:
		break;
	}

	return -ENOTSUPP;
}