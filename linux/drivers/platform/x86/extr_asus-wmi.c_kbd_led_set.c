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
struct led_classdev {int flags; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int LED_UNREGISTERING ; 
 int /*<<< orphan*/  do_kbd_led_set (struct led_classdev*,int) ; 

__attribute__((used)) static void kbd_led_set(struct led_classdev *led_cdev,
			enum led_brightness value)
{
	/* Prevent disabling keyboard backlight on module unregister */
	if (led_cdev->flags & LED_UNREGISTERING)
		return;

	do_kbd_led_set(led_cdev, value);
}