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
struct led_classdev {int /*<<< orphan*/  max_brightness; } ;

/* Variables and functions */
 int /*<<< orphan*/  led_set_brightness_nosleep (struct led_classdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int defon_trig_activate(struct led_classdev *led_cdev)
{
	led_set_brightness_nosleep(led_cdev, led_cdev->max_brightness);
	return 0;
}