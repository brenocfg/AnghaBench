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
struct led_classdev {int new_blink_brightness; int /*<<< orphan*/  work_flags; int /*<<< orphan*/  set_brightness_work; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int /*<<< orphan*/  LED_BLINK_BRIGHTNESS_CHANGE ; 
 int /*<<< orphan*/  LED_BLINK_DISABLE ; 
 int /*<<< orphan*/  LED_BLINK_SW ; 
 int LED_OFF ; 
 int /*<<< orphan*/  led_set_brightness_nosleep (struct led_classdev*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void led_set_brightness(struct led_classdev *led_cdev,
			enum led_brightness brightness)
{
	/*
	 * If software blink is active, delay brightness setting
	 * until the next timer tick.
	 */
	if (test_bit(LED_BLINK_SW, &led_cdev->work_flags)) {
		/*
		 * If we need to disable soft blinking delegate this to the
		 * work queue task to avoid problems in case we are called
		 * from hard irq context.
		 */
		if (brightness == LED_OFF) {
			set_bit(LED_BLINK_DISABLE, &led_cdev->work_flags);
			schedule_work(&led_cdev->set_brightness_work);
		} else {
			set_bit(LED_BLINK_BRIGHTNESS_CHANGE,
				&led_cdev->work_flags);
			led_cdev->new_blink_brightness = brightness;
		}
		return;
	}

	led_set_brightness_nosleep(led_cdev, brightness);
}