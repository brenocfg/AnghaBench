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
typedef  int u32 ;
struct led_classdev {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int /*<<< orphan*/  GPO_BLINK ; 
 int /*<<< orphan*/  GP_LVL ; 
 int LED_HALF ; 
 int /*<<< orphan*/  __nasgpio_led_set_attr (struct led_classdev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nasgpio_gpio_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nasgpio_led_set_brightness(struct led_classdev *led_cdev,
				       enum led_brightness brightness)
{
	u32 setting = 0;
	if (brightness >= LED_HALF)
		setting = 1;
	/*
	 * Hold the lock across both operations.  This ensures
	 * consistency so that both the "turn off blinking"
	 * and "turn light off" operations complete as a set.
	 */
	spin_lock(&nasgpio_gpio_lock);
	/*
	 * LED class documentation asks that past blink state
	 * be disabled when brightness is turned to zero.
	 */
	if (brightness == 0)
		__nasgpio_led_set_attr(led_cdev, GPO_BLINK, 0);
	__nasgpio_led_set_attr(led_cdev, GP_LVL, setting);
	spin_unlock(&nasgpio_gpio_lock);
}