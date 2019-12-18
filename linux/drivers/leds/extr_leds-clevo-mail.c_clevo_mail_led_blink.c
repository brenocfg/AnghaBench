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
struct led_classdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEVO_MAIL_LED_BLINK_0_5HZ ; 
 int /*<<< orphan*/  CLEVO_MAIL_LED_BLINK_1HZ ; 
 int EINVAL ; 
 int /*<<< orphan*/  i8042_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i8042_lock_chip () ; 
 int /*<<< orphan*/  i8042_unlock_chip () ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,unsigned long) ; 

__attribute__((used)) static int clevo_mail_led_blink(struct led_classdev *led_cdev,
				unsigned long *delay_on,
				unsigned long *delay_off)
{
	int status = -EINVAL;

	i8042_lock_chip();

	if (*delay_on == 0 /* ms */ && *delay_off == 0 /* ms */) {
		/* Special case: the leds subsystem requested us to
		 * chose one user friendly blinking of the LED, and
		 * start it. Let's blink the led slowly (0.5Hz).
		 */
		*delay_on = 1000; /* ms */
		*delay_off = 1000; /* ms */
		i8042_command(NULL, CLEVO_MAIL_LED_BLINK_0_5HZ);
		status = 0;

	} else if (*delay_on == 500 /* ms */ && *delay_off == 500 /* ms */) {
		/* blink the led with 1Hz */
		i8042_command(NULL, CLEVO_MAIL_LED_BLINK_1HZ);
		status = 0;

	} else if (*delay_on == 1000 /* ms */ && *delay_off == 1000 /* ms */) {
		/* blink the led with 0.5Hz */
		i8042_command(NULL, CLEVO_MAIL_LED_BLINK_0_5HZ);
		status = 0;

	} else {
		pr_debug("clevo_mail_led_blink(..., %lu, %lu),"
		       " returning -EINVAL (unsupported)\n",
		       *delay_on, *delay_off);
	}

	i8042_unlock_chip();

	return status;
}