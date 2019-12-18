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
struct led_classdev {int flags; int /*<<< orphan*/  blink_delay_off; int /*<<< orphan*/  blink_delay_on; int /*<<< orphan*/  set_brightness_work; } ;

/* Variables and functions */
 int LED_INIT_DEFAULT_TRIGGER ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_blink_set (struct led_classdev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pattern_init (struct led_classdev*) ; 

__attribute__((used)) static int timer_trig_activate(struct led_classdev *led_cdev)
{
	if (led_cdev->flags & LED_INIT_DEFAULT_TRIGGER) {
		pattern_init(led_cdev);
		/*
		 * Mark as initialized even on pattern_init() error because
		 * any consecutive call to it would produce the same error.
		 */
		led_cdev->flags &= ~LED_INIT_DEFAULT_TRIGGER;
	}

	/*
	 * If "set brightness to 0" is pending in workqueue, we don't
	 * want that to be reordered after blink_set()
	 */
	flush_work(&led_cdev->set_brightness_work);
	led_blink_set(led_cdev, &led_cdev->blink_delay_on,
		      &led_cdev->blink_delay_off);

	return 0;
}