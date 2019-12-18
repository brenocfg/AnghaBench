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
struct pwm_state {int enabled; int duty_cycle; int /*<<< orphan*/  period; } ;
struct pwm_device {int /*<<< orphan*/  hwpwm; } ;
struct pwm_chip {int /*<<< orphan*/  dev; } ;
struct cros_ec_pwm_device {int /*<<< orphan*/  ec; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_PWM_MAX_DUTY ; 
 int cros_ec_pwm_get_duty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct cros_ec_pwm_device* pwm_to_cros_ec_pwm (struct pwm_chip*) ; 

__attribute__((used)) static void cros_ec_pwm_get_state(struct pwm_chip *chip, struct pwm_device *pwm,
				  struct pwm_state *state)
{
	struct cros_ec_pwm_device *ec_pwm = pwm_to_cros_ec_pwm(chip);
	int ret;

	ret = cros_ec_pwm_get_duty(ec_pwm->ec, pwm->hwpwm);
	if (ret < 0) {
		dev_err(chip->dev, "error getting initial duty: %d\n", ret);
		return;
	}

	state->enabled = (ret > 0);
	state->period = EC_PWM_MAX_DUTY;

	/* Note that "disabled" and "duty cycle == 0" are treated the same */
	state->duty_cycle = ret;
}