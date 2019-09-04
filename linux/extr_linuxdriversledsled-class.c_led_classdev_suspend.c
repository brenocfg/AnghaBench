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
struct led_classdev {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_SUSPENDED ; 
 int /*<<< orphan*/  led_set_brightness_nopm (struct led_classdev*,int /*<<< orphan*/ ) ; 

void led_classdev_suspend(struct led_classdev *led_cdev)
{
	led_cdev->flags |= LED_SUSPENDED;
	led_set_brightness_nopm(led_cdev, 0);
}