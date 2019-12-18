#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pwm_state {scalar_t__ polarity; scalar_t__ period; scalar_t__ enabled; } ;
struct pwm_device {int hwpwm; } ;
struct pwm_chip {int /*<<< orphan*/  dev; } ;
struct atmel_pwm_chip {int updated_pwms; int /*<<< orphan*/  isr_lock; int /*<<< orphan*/  clk; TYPE_2__* data; } ;
struct TYPE_3__ {int /*<<< orphan*/  period; } ;
struct TYPE_4__ {TYPE_1__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWM_CMR ; 
 int PWM_CMR_CPOL ; 
 int PWM_CMR_CPRE_MSK ; 
 int /*<<< orphan*/  PWM_ENA ; 
 int /*<<< orphan*/  PWM_ISR ; 
 scalar_t__ PWM_POLARITY_NORMAL ; 
 int /*<<< orphan*/  atmel_pwm_calculate_cdty (struct pwm_state const*,unsigned long,unsigned long*) ; 
 int atmel_pwm_calculate_cprd_and_pres (struct pwm_chip*,struct pwm_state const*,unsigned long*,int*) ; 
 void* atmel_pwm_ch_readl (struct atmel_pwm_chip*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_pwm_ch_writel (struct atmel_pwm_chip*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atmel_pwm_disable (struct pwm_chip*,struct pwm_device*,int) ; 
 int atmel_pwm_readl (struct atmel_pwm_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_pwm_set_cprd_cdty (struct pwm_chip*,struct pwm_device*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  atmel_pwm_update_cdty (struct pwm_chip*,struct pwm_device*,unsigned long) ; 
 int /*<<< orphan*/  atmel_pwm_writel (struct atmel_pwm_chip*,int /*<<< orphan*/ ,int) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwm_get_state (struct pwm_device*,struct pwm_state*) ; 
 struct atmel_pwm_chip* to_atmel_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static int atmel_pwm_apply(struct pwm_chip *chip, struct pwm_device *pwm,
			   const struct pwm_state *state)
{
	struct atmel_pwm_chip *atmel_pwm = to_atmel_pwm_chip(chip);
	struct pwm_state cstate;
	unsigned long cprd, cdty;
	u32 pres, val;
	int ret;

	pwm_get_state(pwm, &cstate);

	if (state->enabled) {
		if (cstate.enabled &&
		    cstate.polarity == state->polarity &&
		    cstate.period == state->period) {
			cprd = atmel_pwm_ch_readl(atmel_pwm, pwm->hwpwm,
						  atmel_pwm->data->regs.period);
			atmel_pwm_calculate_cdty(state, cprd, &cdty);
			atmel_pwm_update_cdty(chip, pwm, cdty);
			return 0;
		}

		ret = atmel_pwm_calculate_cprd_and_pres(chip, state, &cprd,
							&pres);
		if (ret) {
			dev_err(chip->dev,
				"failed to calculate cprd and prescaler\n");
			return ret;
		}

		atmel_pwm_calculate_cdty(state, cprd, &cdty);

		if (cstate.enabled) {
			atmel_pwm_disable(chip, pwm, false);
		} else {
			ret = clk_enable(atmel_pwm->clk);
			if (ret) {
				dev_err(chip->dev, "failed to enable clock\n");
				return ret;
			}
		}

		/* It is necessary to preserve CPOL, inside CMR */
		val = atmel_pwm_ch_readl(atmel_pwm, pwm->hwpwm, PWM_CMR);
		val = (val & ~PWM_CMR_CPRE_MSK) | (pres & PWM_CMR_CPRE_MSK);
		if (state->polarity == PWM_POLARITY_NORMAL)
			val &= ~PWM_CMR_CPOL;
		else
			val |= PWM_CMR_CPOL;
		atmel_pwm_ch_writel(atmel_pwm, pwm->hwpwm, PWM_CMR, val);
		atmel_pwm_set_cprd_cdty(chip, pwm, cprd, cdty);
		mutex_lock(&atmel_pwm->isr_lock);
		atmel_pwm->updated_pwms |= atmel_pwm_readl(atmel_pwm, PWM_ISR);
		atmel_pwm->updated_pwms &= ~(1 << pwm->hwpwm);
		mutex_unlock(&atmel_pwm->isr_lock);
		atmel_pwm_writel(atmel_pwm, PWM_ENA, 1 << pwm->hwpwm);
	} else if (cstate.enabled) {
		atmel_pwm_disable(chip, pwm, true);
	}

	return 0;
}