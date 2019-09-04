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
struct wm831x_gpio {struct wm831x* wm831x; } ;
struct wm831x {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 130 
#define  PIN_CONFIG_DRIVE_PUSH_PULL 129 
#define  PIN_CONFIG_INPUT_DEBOUNCE 128 
 unsigned int WM831X_GPIO1_CONTROL ; 
 int /*<<< orphan*/  WM831X_GPN_OD ; 
 int /*<<< orphan*/  WM831X_GPN_OD_MASK ; 
 struct wm831x_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  pinconf_to_config_argument (unsigned long) ; 
 int pinconf_to_config_param (unsigned long) ; 
 int wm831x_gpio_set_debounce (struct wm831x*,unsigned int,int /*<<< orphan*/ ) ; 
 int wm831x_set_bits (struct wm831x*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm831x_set_config(struct gpio_chip *chip, unsigned int offset,
			     unsigned long config)
{
	struct wm831x_gpio *wm831x_gpio = gpiochip_get_data(chip);
	struct wm831x *wm831x = wm831x_gpio->wm831x;
	int reg = WM831X_GPIO1_CONTROL + offset;

	switch (pinconf_to_config_param(config)) {
	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
		return wm831x_set_bits(wm831x, reg,
				       WM831X_GPN_OD_MASK, WM831X_GPN_OD);
	case PIN_CONFIG_DRIVE_PUSH_PULL:
		return wm831x_set_bits(wm831x, reg,
				       WM831X_GPN_OD_MASK, 0);
	case PIN_CONFIG_INPUT_DEBOUNCE:
		return wm831x_gpio_set_debounce(wm831x, offset,
			pinconf_to_config_argument(config));
	default:
		break;
	}

	return -ENOTSUPP;
}