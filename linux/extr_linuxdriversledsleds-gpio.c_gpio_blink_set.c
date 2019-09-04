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
struct led_classdev {int dummy; } ;
struct gpio_led_data {int blinking; int (* platform_gpio_blink_set ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*,unsigned long*) ;int /*<<< orphan*/  gpiod; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_LED_BLINK ; 
 struct gpio_led_data* cdev_to_gpio_led_data (struct led_classdev*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*,unsigned long*) ; 

__attribute__((used)) static int gpio_blink_set(struct led_classdev *led_cdev,
	unsigned long *delay_on, unsigned long *delay_off)
{
	struct gpio_led_data *led_dat = cdev_to_gpio_led_data(led_cdev);

	led_dat->blinking = 1;
	return led_dat->platform_gpio_blink_set(led_dat->gpiod, GPIO_LED_BLINK,
						delay_on, delay_off);
}