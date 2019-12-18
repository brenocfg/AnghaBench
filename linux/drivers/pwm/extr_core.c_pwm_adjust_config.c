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
typedef  int u64 ;
struct pwm_state {int period; int duty_cycle; scalar_t__ polarity; } ;
struct pwm_device {int dummy; } ;
struct pwm_args {int period; scalar_t__ polarity; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,int) ; 
 int pwm_apply_state (struct pwm_device*,struct pwm_state*) ; 
 int /*<<< orphan*/  pwm_get_args (struct pwm_device*,struct pwm_args*) ; 
 int /*<<< orphan*/  pwm_get_state (struct pwm_device*,struct pwm_state*) ; 

int pwm_adjust_config(struct pwm_device *pwm)
{
	struct pwm_state state;
	struct pwm_args pargs;

	pwm_get_args(pwm, &pargs);
	pwm_get_state(pwm, &state);

	/*
	 * If the current period is zero it means that either the PWM driver
	 * does not support initial state retrieval or the PWM has not yet
	 * been configured.
	 *
	 * In either case, we setup the new period and polarity, and assign a
	 * duty cycle of 0.
	 */
	if (!state.period) {
		state.duty_cycle = 0;
		state.period = pargs.period;
		state.polarity = pargs.polarity;

		return pwm_apply_state(pwm, &state);
	}

	/*
	 * Adjust the PWM duty cycle/period based on the period value provided
	 * in PWM args.
	 */
	if (pargs.period != state.period) {
		u64 dutycycle = (u64)state.duty_cycle * pargs.period;

		do_div(dutycycle, state.period);
		state.duty_cycle = dutycycle;
		state.period = pargs.period;
	}

	/*
	 * If the polarity changed, we should also change the duty cycle.
	 */
	if (pargs.polarity != state.polarity) {
		state.polarity = pargs.polarity;
		state.duty_cycle = state.period - state.duty_cycle;
	}

	return pwm_apply_state(pwm, &state);
}