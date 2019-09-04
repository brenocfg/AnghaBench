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

/* Variables and functions */
 int /*<<< orphan*/  DSMG600_LED_PWR_GPIO ; 
 int /*<<< orphan*/  DSMG600_PB_GPIO ; 
 scalar_t__ PBUTTON_HOLDDOWN_COUNT ; 
 int /*<<< orphan*/  ctrl_alt_del () ; 
 int /*<<< orphan*/  dsmg600_power_timer ; 
 scalar_t__ gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 scalar_t__ power_button_countdown ; 

__attribute__((used)) static void dsmg600_power_handler(struct timer_list *unused)
{
	/* This routine is called twice per second to check the
	 * state of the power button.
	 */

	if (gpio_get_value(DSMG600_PB_GPIO)) {

		/* IO Pin is 1 (button pushed) */
		if (power_button_countdown > 0)
			power_button_countdown--;

	} else {

		/* Done on button release, to allow for auto-power-on mods. */
		if (power_button_countdown == 0) {
			/* Signal init to do the ctrlaltdel action,
			 * this will bypass init if it hasn't started
			 * and do a kernel_restart.
			 */
			ctrl_alt_del();

			/* Change the state of the power LED to "blink" */
			gpio_set_value(DSMG600_LED_PWR_GPIO, 0);
		} else {
			power_button_countdown = PBUTTON_HOLDDOWN_COUNT;
		}
	}

	mod_timer(&dsmg600_power_timer, jiffies + msecs_to_jiffies(500));
}