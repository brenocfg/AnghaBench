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
struct led_classdev {int /*<<< orphan*/  blink_delay_off; int /*<<< orphan*/  blink_delay_on; } ;

/* Variables and functions */
 int /*<<< orphan*/  led_blink_set (struct led_classdev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int timer_trig_activate(struct led_classdev *led_cdev)
{
	led_blink_set(led_cdev, &led_cdev->blink_delay_on,
		      &led_cdev->blink_delay_off);

	return 0;
}