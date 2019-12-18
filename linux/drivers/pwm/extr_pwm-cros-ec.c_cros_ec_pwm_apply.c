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
struct pwm_state {scalar_t__ period; int duty_cycle; scalar_t__ enabled; } ;
struct pwm_device {int /*<<< orphan*/  hwpwm; } ;
struct pwm_chip {int dummy; } ;
struct cros_ec_pwm_device {int /*<<< orphan*/  ec; } ;

/* Variables and functions */
 scalar_t__ EC_PWM_MAX_DUTY ; 
 int EINVAL ; 
 int cros_ec_pwm_set_duty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct cros_ec_pwm_device* pwm_to_cros_ec_pwm (struct pwm_chip*) ; 

__attribute__((used)) static int cros_ec_pwm_apply(struct pwm_chip *chip, struct pwm_device *pwm,
			     const struct pwm_state *state)
{
	struct cros_ec_pwm_device *ec_pwm = pwm_to_cros_ec_pwm(chip);
	int duty_cycle;

	/* The EC won't let us change the period */
	if (state->period != EC_PWM_MAX_DUTY)
		return -EINVAL;

	/*
	 * EC doesn't separate the concept of duty cycle and enabled, but
	 * kernel does. Translate.
	 */
	duty_cycle = state->enabled ? state->duty_cycle : 0;

	return cros_ec_pwm_set_duty(ec_pwm->ec, pwm->hwpwm, duty_cycle);
}