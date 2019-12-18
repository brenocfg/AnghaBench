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
struct asus_wmi {int /*<<< orphan*/  kbd_led_wk; struct led_classdev kbd_led; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int /*<<< orphan*/  do_kbd_led_set (struct led_classdev*,int) ; 
 int /*<<< orphan*/  led_classdev_notify_brightness_hw_changed (struct led_classdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kbd_led_set_by_kbd(struct asus_wmi *asus, enum led_brightness value)
{
	struct led_classdev *led_cdev = &asus->kbd_led;

	do_kbd_led_set(led_cdev, value);
	led_classdev_notify_brightness_hw_changed(led_cdev, asus->kbd_led_wk);
}