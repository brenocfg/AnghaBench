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
 int /*<<< orphan*/  SET_GPIO_OUTPUT ; 
 int /*<<< orphan*/  led_set_brightness (struct led_classdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void input_trig_deactivate(struct led_classdev *led_cdev)
{
	led_cdev->flags |= SET_GPIO_OUTPUT;
	led_set_brightness(led_cdev, 0);
}