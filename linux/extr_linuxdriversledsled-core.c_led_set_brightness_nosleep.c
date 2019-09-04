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
struct led_classdev {int flags; int /*<<< orphan*/  brightness; int /*<<< orphan*/  max_brightness; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int LED_SUSPENDED ; 
 int /*<<< orphan*/  led_set_brightness_nopm (struct led_classdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 

void led_set_brightness_nosleep(struct led_classdev *led_cdev,
				enum led_brightness value)
{
	led_cdev->brightness = min(value, led_cdev->max_brightness);

	if (led_cdev->flags & LED_SUSPENDED)
		return;

	led_set_brightness_nopm(led_cdev, led_cdev->brightness);
}