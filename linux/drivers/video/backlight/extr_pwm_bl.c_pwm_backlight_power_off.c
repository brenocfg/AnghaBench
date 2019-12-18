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
struct pwm_state {int enabled; scalar_t__ duty_cycle; } ;
struct pwm_bl_data {int enabled; int /*<<< orphan*/  power_supply; int /*<<< orphan*/  pwm; scalar_t__ pwm_off_delay; scalar_t__ enable_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 
 int /*<<< orphan*/  pwm_apply_state (int /*<<< orphan*/ ,struct pwm_state*) ; 
 int /*<<< orphan*/  pwm_get_state (int /*<<< orphan*/ ,struct pwm_state*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pwm_backlight_power_off(struct pwm_bl_data *pb)
{
	struct pwm_state state;

	pwm_get_state(pb->pwm, &state);
	if (!pb->enabled)
		return;

	if (pb->enable_gpio)
		gpiod_set_value_cansleep(pb->enable_gpio, 0);

	if (pb->pwm_off_delay)
		msleep(pb->pwm_off_delay);

	state.enabled = false;
	state.duty_cycle = 0;
	pwm_apply_state(pb->pwm, &state);

	regulator_disable(pb->power_supply);
	pb->enabled = false;
}