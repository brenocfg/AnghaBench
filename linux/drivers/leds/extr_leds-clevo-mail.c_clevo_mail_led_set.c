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
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int /*<<< orphan*/  CLEVO_MAIL_LED_BLINK_0_5HZ ; 
 int /*<<< orphan*/  CLEVO_MAIL_LED_BLINK_1HZ ; 
 int /*<<< orphan*/  CLEVO_MAIL_LED_OFF ; 
 int LED_HALF ; 
 int LED_OFF ; 
 int /*<<< orphan*/  i8042_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i8042_lock_chip () ; 
 int /*<<< orphan*/  i8042_unlock_chip () ; 

__attribute__((used)) static void clevo_mail_led_set(struct led_classdev *led_cdev,
				enum led_brightness value)
{
	i8042_lock_chip();

	if (value == LED_OFF)
		i8042_command(NULL, CLEVO_MAIL_LED_OFF);
	else if (value <= LED_HALF)
		i8042_command(NULL, CLEVO_MAIL_LED_BLINK_0_5HZ);
	else
		i8042_command(NULL, CLEVO_MAIL_LED_BLINK_1HZ);

	i8042_unlock_chip();

}