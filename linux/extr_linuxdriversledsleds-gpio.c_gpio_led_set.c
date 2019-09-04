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
struct led_classdev {int dummy; } ;
struct TYPE_2__ {int flags; } ;
struct gpio_led_data {int /*<<< orphan*/  gpiod; TYPE_1__ cdev; scalar_t__ can_sleep; scalar_t__ blinking; int /*<<< orphan*/  (* platform_gpio_blink_set ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int LED_OFF ; 
 int SET_GPIO_INPUT ; 
 int SET_GPIO_OUTPUT ; 
 struct gpio_led_data* cdev_to_gpio_led_data (struct led_classdev*) ; 
 int /*<<< orphan*/  gpiod_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gpio_led_set(struct led_classdev *led_cdev,
	enum led_brightness value)
{
	struct gpio_led_data *led_dat = cdev_to_gpio_led_data(led_cdev);
	int level;

	if (value == LED_OFF)
		level = 0;
	else
		level = 1;

	if (led_dat->blinking) {
		led_dat->platform_gpio_blink_set(led_dat->gpiod, level,
						 NULL, NULL);
		led_dat->blinking = 0;
	} else if (led_dat->cdev.flags & SET_GPIO_INPUT) {
		gpiod_direction_input(led_dat->gpiod);
		led_dat->cdev.flags &= ~SET_GPIO_INPUT;
	} else if (led_dat->cdev.flags & SET_GPIO_OUTPUT) {
		gpiod_direction_output(led_dat->gpiod, level);
		led_dat->cdev.flags &= ~SET_GPIO_OUTPUT;
	} else {
		if (led_dat->can_sleep ||
			(led_dat->cdev.flags & (SET_GPIO_INPUT | SET_GPIO_OUTPUT) ))
			gpiod_set_value_cansleep(led_dat->gpiod, level);
		else
			gpiod_set_value(led_dat->gpiod, level);
	}
}