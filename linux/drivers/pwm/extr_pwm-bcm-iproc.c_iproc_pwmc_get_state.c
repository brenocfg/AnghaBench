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
typedef  int u32 ;
struct pwm_state {int enabled; void* duty_cycle; void* period; int /*<<< orphan*/  polarity; } ;
struct pwm_device {int /*<<< orphan*/  hwpwm; } ;
struct pwm_chip {int dummy; } ;
struct iproc_pwmc {scalar_t__ base; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPROC_PWM_CTRL_EN_SHIFT (int /*<<< orphan*/ ) ; 
 scalar_t__ IPROC_PWM_CTRL_OFFSET ; 
 int /*<<< orphan*/  IPROC_PWM_CTRL_POLARITY_SHIFT (int /*<<< orphan*/ ) ; 
 scalar_t__ IPROC_PWM_DUTY_CYCLE_OFFSET (int /*<<< orphan*/ ) ; 
 int IPROC_PWM_PERIOD_MAX ; 
 scalar_t__ IPROC_PWM_PERIOD_OFFSET (int /*<<< orphan*/ ) ; 
 int IPROC_PWM_PRESCALE_MAX ; 
 scalar_t__ IPROC_PWM_PRESCALE_OFFSET ; 
 int IPROC_PWM_PRESCALE_SHIFT (int /*<<< orphan*/ ) ; 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  PWM_POLARITY_INVERSED ; 
 int /*<<< orphan*/  PWM_POLARITY_NORMAL ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 void* div64_u64 (int,int) ; 
 int readl (scalar_t__) ; 
 struct iproc_pwmc* to_iproc_pwmc (struct pwm_chip*) ; 

__attribute__((used)) static void iproc_pwmc_get_state(struct pwm_chip *chip, struct pwm_device *pwm,
				 struct pwm_state *state)
{
	struct iproc_pwmc *ip = to_iproc_pwmc(chip);
	u64 tmp, multi, rate;
	u32 value, prescale;

	rate = clk_get_rate(ip->clk);

	value = readl(ip->base + IPROC_PWM_CTRL_OFFSET);

	if (value & BIT(IPROC_PWM_CTRL_EN_SHIFT(pwm->hwpwm)))
		state->enabled = true;
	else
		state->enabled = false;

	if (value & BIT(IPROC_PWM_CTRL_POLARITY_SHIFT(pwm->hwpwm)))
		state->polarity = PWM_POLARITY_NORMAL;
	else
		state->polarity = PWM_POLARITY_INVERSED;

	value = readl(ip->base + IPROC_PWM_PRESCALE_OFFSET);
	prescale = value >> IPROC_PWM_PRESCALE_SHIFT(pwm->hwpwm);
	prescale &= IPROC_PWM_PRESCALE_MAX;

	multi = NSEC_PER_SEC * (prescale + 1);

	value = readl(ip->base + IPROC_PWM_PERIOD_OFFSET(pwm->hwpwm));
	tmp = (value & IPROC_PWM_PERIOD_MAX) * multi;
	state->period = div64_u64(tmp, rate);

	value = readl(ip->base + IPROC_PWM_DUTY_CYCLE_OFFSET(pwm->hwpwm));
	tmp = (value & IPROC_PWM_PERIOD_MAX) * multi;
	state->duty_cycle = div64_u64(tmp, rate);
}