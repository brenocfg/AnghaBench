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
struct led_classdev {int /*<<< orphan*/  work_flags; int /*<<< orphan*/  blink_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_BLINK_INVERT ; 
 int /*<<< orphan*/  LED_BLINK_ONESHOT ; 
 int /*<<< orphan*/  LED_BLINK_ONESHOT_STOP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_blink_setup (struct led_classdev*,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

void led_blink_set_oneshot(struct led_classdev *led_cdev,
			   unsigned long *delay_on,
			   unsigned long *delay_off,
			   int invert)
{
	if (test_bit(LED_BLINK_ONESHOT, &led_cdev->work_flags) &&
	     timer_pending(&led_cdev->blink_timer))
		return;

	set_bit(LED_BLINK_ONESHOT, &led_cdev->work_flags);
	clear_bit(LED_BLINK_ONESHOT_STOP, &led_cdev->work_flags);

	if (invert)
		set_bit(LED_BLINK_INVERT, &led_cdev->work_flags);
	else
		clear_bit(LED_BLINK_INVERT, &led_cdev->work_flags);

	led_blink_setup(led_cdev, delay_on, delay_off);
}