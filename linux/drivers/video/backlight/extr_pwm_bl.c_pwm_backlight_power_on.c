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
struct pwm_state {int enabled; } ;
struct pwm_bl_data {int enabled; scalar_t__ enable_gpio; scalar_t__ post_pwm_on_delay; int /*<<< orphan*/  pwm; int /*<<< orphan*/  dev; int /*<<< orphan*/  power_supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 
 int /*<<< orphan*/  pwm_apply_state (int /*<<< orphan*/ ,struct pwm_state*) ; 
 int /*<<< orphan*/  pwm_get_state (int /*<<< orphan*/ ,struct pwm_state*) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pwm_backlight_power_on(struct pwm_bl_data *pb)
{
	struct pwm_state state;
	int err;

	pwm_get_state(pb->pwm, &state);
	if (pb->enabled)
		return;

	err = regulator_enable(pb->power_supply);
	if (err < 0)
		dev_err(pb->dev, "failed to enable power supply\n");

	state.enabled = true;
	pwm_apply_state(pb->pwm, &state);

	if (pb->post_pwm_on_delay)
		msleep(pb->post_pwm_on_delay);

	if (pb->enable_gpio)
		gpiod_set_value_cansleep(pb->enable_gpio, 1);

	pb->enabled = true;
}