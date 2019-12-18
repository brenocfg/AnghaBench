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
struct rcar_pwm_chip {int dummy; } ;
struct pwm_state {scalar_t__ polarity; int /*<<< orphan*/  period; int /*<<< orphan*/  duty_cycle; int /*<<< orphan*/  enabled; } ;
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 scalar_t__ PWM_POLARITY_NORMAL ; 
 int /*<<< orphan*/  RCAR_PWMCR ; 
 int /*<<< orphan*/  RCAR_PWMCR_SYNC ; 
 int /*<<< orphan*/  pwm_get_state (struct pwm_device*,struct pwm_state*) ; 
 int /*<<< orphan*/  rcar_pwm_disable (struct rcar_pwm_chip*) ; 
 int rcar_pwm_enable (struct rcar_pwm_chip*) ; 
 int rcar_pwm_get_clock_division (struct rcar_pwm_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_pwm_set_clock_control (struct rcar_pwm_chip*,int) ; 
 int rcar_pwm_set_counter (struct rcar_pwm_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_pwm_update (struct rcar_pwm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rcar_pwm_chip* to_rcar_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static int rcar_pwm_apply(struct pwm_chip *chip, struct pwm_device *pwm,
			  const struct pwm_state *state)
{
	struct rcar_pwm_chip *rp = to_rcar_pwm_chip(chip);
	struct pwm_state cur_state;
	int div, ret;

	/* This HW/driver only supports normal polarity */
	pwm_get_state(pwm, &cur_state);
	if (state->polarity != PWM_POLARITY_NORMAL)
		return -ENOTSUPP;

	if (!state->enabled) {
		rcar_pwm_disable(rp);
		return 0;
	}

	div = rcar_pwm_get_clock_division(rp, state->period);
	if (div < 0)
		return div;

	rcar_pwm_update(rp, RCAR_PWMCR_SYNC, RCAR_PWMCR_SYNC, RCAR_PWMCR);

	ret = rcar_pwm_set_counter(rp, div, state->duty_cycle, state->period);
	if (!ret)
		rcar_pwm_set_clock_control(rp, div);

	/* The SYNC should be set to 0 even if rcar_pwm_set_counter failed */
	rcar_pwm_update(rp, RCAR_PWMCR_SYNC, 0, RCAR_PWMCR);

	if (!ret)
		ret = rcar_pwm_enable(rp);

	return ret;
}