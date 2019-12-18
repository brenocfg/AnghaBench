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
typedef  int uint16_t ;
struct pwm_state {unsigned long long period; unsigned long long duty_cycle; int polarity; scalar_t__ enabled; } ;
struct pwm_device {int /*<<< orphan*/  hwpwm; int /*<<< orphan*/  chip; } ;
struct pwm_chip {int dummy; } ;
struct jz4740_pwm_chip {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int EINVAL ; 
 int JZ_TIMER_CTRL_PRESCALER (unsigned int) ; 
 int JZ_TIMER_CTRL_PWM_ABBRUPT_SHUTDOWN ; 
 int JZ_TIMER_CTRL_PWM_ACTIVE_LOW ; 
 int JZ_TIMER_CTRL_SRC_EXT ; 
#define  PWM_POLARITY_INVERSED 129 
#define  PWM_POLARITY_NORMAL 128 
 scalar_t__ clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 
 int /*<<< orphan*/  jz4740_pwm_disable (struct pwm_chip*,struct pwm_device*) ; 
 int /*<<< orphan*/  jz4740_pwm_enable (struct pwm_chip*,struct pwm_device*) ; 
 int /*<<< orphan*/  jz4740_timer_set_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4740_timer_set_ctrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jz4740_timer_set_duty (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  jz4740_timer_set_period (int /*<<< orphan*/ ,unsigned long) ; 
 struct jz4740_pwm_chip* to_jz4740 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jz4740_pwm_apply(struct pwm_chip *chip, struct pwm_device *pwm,
			    const struct pwm_state *state)
{
	struct jz4740_pwm_chip *jz4740 = to_jz4740(pwm->chip);
	unsigned long long tmp;
	unsigned long period, duty;
	unsigned int prescaler = 0;
	uint16_t ctrl;

	tmp = (unsigned long long)clk_get_rate(jz4740->clk) * state->period;
	do_div(tmp, 1000000000);
	period = tmp;

	while (period > 0xffff && prescaler < 6) {
		period >>= 2;
		++prescaler;
	}

	if (prescaler == 6)
		return -EINVAL;

	tmp = (unsigned long long)period * state->duty_cycle;
	do_div(tmp, state->period);
	duty = period - tmp;

	if (duty >= period)
		duty = period - 1;

	jz4740_pwm_disable(chip, pwm);

	jz4740_timer_set_count(pwm->hwpwm, 0);
	jz4740_timer_set_duty(pwm->hwpwm, duty);
	jz4740_timer_set_period(pwm->hwpwm, period);

	ctrl = JZ_TIMER_CTRL_PRESCALER(prescaler) | JZ_TIMER_CTRL_SRC_EXT |
		JZ_TIMER_CTRL_PWM_ABBRUPT_SHUTDOWN;

	jz4740_timer_set_ctrl(pwm->hwpwm, ctrl);

	switch (state->polarity) {
	case PWM_POLARITY_NORMAL:
		ctrl &= ~JZ_TIMER_CTRL_PWM_ACTIVE_LOW;
		break;
	case PWM_POLARITY_INVERSED:
		ctrl |= JZ_TIMER_CTRL_PWM_ACTIVE_LOW;
		break;
	}

	jz4740_timer_set_ctrl(pwm->hwpwm, ctrl);

	if (state->enabled)
		jz4740_pwm_enable(chip, pwm);

	return 0;
}