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
struct timer_list {int dummy; } ;
struct led_classdev {unsigned long blink_delay_on; unsigned long blink_delay_off; unsigned long new_blink_brightness; unsigned long blink_brightness; int /*<<< orphan*/  blink_timer; int /*<<< orphan*/  work_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_BLINK_BRIGHTNESS_CHANGE ; 
 int /*<<< orphan*/  LED_BLINK_INVERT ; 
 int /*<<< orphan*/  LED_BLINK_ONESHOT ; 
 int /*<<< orphan*/  LED_BLINK_ONESHOT_STOP ; 
 int /*<<< orphan*/  LED_BLINK_SW ; 
 unsigned long LED_OFF ; 
 int /*<<< orphan*/  blink_timer ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct led_classdev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 struct led_classdev* led_cdev ; 
 unsigned long led_get_brightness (struct led_classdev*) ; 
 int /*<<< orphan*/  led_set_brightness_nosleep (struct led_classdev*,unsigned long) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void led_timer_function(struct timer_list *t)
{
	struct led_classdev *led_cdev = from_timer(led_cdev, t, blink_timer);
	unsigned long brightness;
	unsigned long delay;

	if (!led_cdev->blink_delay_on || !led_cdev->blink_delay_off) {
		led_set_brightness_nosleep(led_cdev, LED_OFF);
		clear_bit(LED_BLINK_SW, &led_cdev->work_flags);
		return;
	}

	if (test_and_clear_bit(LED_BLINK_ONESHOT_STOP,
			       &led_cdev->work_flags)) {
		clear_bit(LED_BLINK_SW, &led_cdev->work_flags);
		return;
	}

	brightness = led_get_brightness(led_cdev);
	if (!brightness) {
		/* Time to switch the LED on. */
		if (test_and_clear_bit(LED_BLINK_BRIGHTNESS_CHANGE,
					&led_cdev->work_flags))
			brightness = led_cdev->new_blink_brightness;
		else
			brightness = led_cdev->blink_brightness;
		delay = led_cdev->blink_delay_on;
	} else {
		/* Store the current brightness value to be able
		 * to restore it when the delay_off period is over.
		 */
		led_cdev->blink_brightness = brightness;
		brightness = LED_OFF;
		delay = led_cdev->blink_delay_off;
	}

	led_set_brightness_nosleep(led_cdev, brightness);

	/* Return in next iteration if led is in one-shot mode and we are in
	 * the final blink state so that the led is toggled each delay_on +
	 * delay_off milliseconds in worst case.
	 */
	if (test_bit(LED_BLINK_ONESHOT, &led_cdev->work_flags)) {
		if (test_bit(LED_BLINK_INVERT, &led_cdev->work_flags)) {
			if (brightness)
				set_bit(LED_BLINK_ONESHOT_STOP,
					&led_cdev->work_flags);
		} else {
			if (!brightness)
				set_bit(LED_BLINK_ONESHOT_STOP,
					&led_cdev->work_flags);
		}
	}

	mod_timer(&led_cdev->blink_timer, jiffies + msecs_to_jiffies(delay));
}