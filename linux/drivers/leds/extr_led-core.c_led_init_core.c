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
struct led_classdev {int /*<<< orphan*/  blink_timer; int /*<<< orphan*/  set_brightness_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_timer_function ; 
 int /*<<< orphan*/  set_brightness_delayed ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void led_init_core(struct led_classdev *led_cdev)
{
	INIT_WORK(&led_cdev->set_brightness_work, set_brightness_delayed);

	timer_setup(&led_cdev->blink_timer, led_timer_function, 0);
}