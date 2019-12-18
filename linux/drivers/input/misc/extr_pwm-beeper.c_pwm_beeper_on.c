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
struct pwm_state {int enabled; unsigned long period; } ;
struct pwm_beeper {int amplifier_on; int /*<<< orphan*/  pwm; int /*<<< orphan*/  amplifier; } ;

/* Variables and functions */
 int pwm_apply_state (int /*<<< orphan*/ ,struct pwm_state*) ; 
 int /*<<< orphan*/  pwm_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_get_state (int /*<<< orphan*/ ,struct pwm_state*) ; 
 int /*<<< orphan*/  pwm_set_relative_duty_cycle (struct pwm_state*,int,int) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pwm_beeper_on(struct pwm_beeper *beeper, unsigned long period)
{
	struct pwm_state state;
	int error;

	pwm_get_state(beeper->pwm, &state);

	state.enabled = true;
	state.period = period;
	pwm_set_relative_duty_cycle(&state, 50, 100);

	error = pwm_apply_state(beeper->pwm, &state);
	if (error)
		return error;

	if (!beeper->amplifier_on) {
		error = regulator_enable(beeper->amplifier);
		if (error) {
			pwm_disable(beeper->pwm);
			return error;
		}

		beeper->amplifier_on = true;
	}

	return 0;
}