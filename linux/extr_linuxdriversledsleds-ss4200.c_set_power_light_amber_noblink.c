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
struct nasgpio_led {int /*<<< orphan*/  led_cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  LED_OFF ; 
 struct nasgpio_led* get_led_named (char*) ; 
 int /*<<< orphan*/  nasgpio_led_set_brightness (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void set_power_light_amber_noblink(void)
{
	struct nasgpio_led *amber = get_led_named("power:amber:power");
	struct nasgpio_led *blue = get_led_named("power:blue:power");

	if (!amber || !blue)
		return;
	/*
	 * LED_OFF implies disabling future blinking
	 */
	pr_debug("setting blue off and amber on\n");

	nasgpio_led_set_brightness(&blue->led_cdev, LED_OFF);
	nasgpio_led_set_brightness(&amber->led_cdev, LED_FULL);
}