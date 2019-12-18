#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct pwm_device {int hwpwm; } ;
struct pwm_chip {int /*<<< orphan*/  dev; } ;
struct atmel_tcb_pwm_device {scalar_t__ duty; scalar_t__ period; int div; } ;
struct atmel_tcb_pwm_chip {struct atmel_tcb_pwm_device** pwms; struct atmel_tc* tc; } ;
struct atmel_tc {TYPE_1__* tcb_config; int /*<<< orphan*/  slow_clk; int /*<<< orphan*/ * clk; } ;
struct TYPE_2__ {unsigned long long counter_width; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int NSEC_PER_SEC ; 
 int* atmel_tc_divisors ; 
 int /*<<< orphan*/  atmel_tcb_pwm_enable (struct pwm_chip*,struct pwm_device*) ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* div_u64 (int,unsigned long long) ; 
 struct atmel_tcb_pwm_device* pwm_get_chip_data (struct pwm_device*) ; 
 scalar_t__ pwm_is_enabled (struct pwm_device*) ; 
 struct atmel_tcb_pwm_chip* to_tcb_chip (struct pwm_chip*) ; 

__attribute__((used)) static int atmel_tcb_pwm_config(struct pwm_chip *chip, struct pwm_device *pwm,
				int duty_ns, int period_ns)
{
	struct atmel_tcb_pwm_chip *tcbpwmc = to_tcb_chip(chip);
	struct atmel_tcb_pwm_device *tcbpwm = pwm_get_chip_data(pwm);
	unsigned group = pwm->hwpwm / 2;
	unsigned index = pwm->hwpwm % 2;
	struct atmel_tcb_pwm_device *atcbpwm = NULL;
	struct atmel_tc *tc = tcbpwmc->tc;
	int i;
	int slowclk = 0;
	unsigned period;
	unsigned duty;
	unsigned rate = clk_get_rate(tc->clk[group]);
	unsigned long long min;
	unsigned long long max;

	/*
	 * Find best clk divisor:
	 * the smallest divisor which can fulfill the period_ns requirements.
	 */
	for (i = 0; i < 5; ++i) {
		if (atmel_tc_divisors[i] == 0) {
			slowclk = i;
			continue;
		}
		min = div_u64((u64)NSEC_PER_SEC * atmel_tc_divisors[i], rate);
		max = min << tc->tcb_config->counter_width;
		if (max >= period_ns)
			break;
	}

	/*
	 * If none of the divisor are small enough to represent period_ns
	 * take slow clock (32KHz).
	 */
	if (i == 5) {
		i = slowclk;
		rate = clk_get_rate(tc->slow_clk);
		min = div_u64(NSEC_PER_SEC, rate);
		max = min << tc->tcb_config->counter_width;

		/* If period is too big return ERANGE error */
		if (max < period_ns)
			return -ERANGE;
	}

	duty = div_u64(duty_ns, min);
	period = div_u64(period_ns, min);

	if (index == 0)
		atcbpwm = tcbpwmc->pwms[pwm->hwpwm + 1];
	else
		atcbpwm = tcbpwmc->pwms[pwm->hwpwm - 1];

	/*
	 * PWM devices provided by TCB driver are grouped by 2:
	 * - group 0: PWM 0 & 1
	 * - group 1: PWM 2 & 3
	 * - group 2: PWM 4 & 5
	 *
	 * PWM devices in a given group must be configured with the
	 * same period_ns.
	 *
	 * We're checking the period value of the second PWM device
	 * in this group before applying the new config.
	 */
	if ((atcbpwm && atcbpwm->duty > 0 &&
			atcbpwm->duty != atcbpwm->period) &&
		(atcbpwm->div != i || atcbpwm->period != period)) {
		dev_err(chip->dev,
			"failed to configure period_ns: PWM group already configured with a different value\n");
		return -EINVAL;
	}

	tcbpwm->period = period;
	tcbpwm->div = i;
	tcbpwm->duty = duty;

	/* If the PWM is enabled, call enable to apply the new conf */
	if (pwm_is_enabled(pwm))
		atmel_tcb_pwm_enable(chip, pwm);

	return 0;
}