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
struct pwm_state {int period; int duty_cycle; scalar_t__ enabled; int /*<<< orphan*/  polarity; } ;
struct pwm_chip {int dummy; } ;
struct imx_tpm_pwm_param {int prescale; int mod; void* val; } ;
struct imx_tpm_pwm_chip {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 void* DIV_ROUND_CLOSEST_ULL (int,int) ; 
 int ERANGE ; 
 int /*<<< orphan*/  FIELD_FIT (int /*<<< orphan*/ ,int) ; 
 int NSEC_PER_SEC ; 
 int PWM_IMX_TPM_MOD_MOD ; 
 int PWM_IMX_TPM_MOD_WIDTH ; 
 int /*<<< orphan*/  PWM_IMX_TPM_SC_PS ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int ilog2 (int) ; 
 struct imx_tpm_pwm_chip* to_imx_tpm_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static int pwm_imx_tpm_round_state(struct pwm_chip *chip,
				   struct imx_tpm_pwm_param *p,
				   struct pwm_state *real_state,
				   const struct pwm_state *state)
{
	struct imx_tpm_pwm_chip *tpm = to_imx_tpm_pwm_chip(chip);
	u32 rate, prescale, period_count, clock_unit;
	u64 tmp;

	rate = clk_get_rate(tpm->clk);
	tmp = (u64)state->period * rate;
	clock_unit = DIV_ROUND_CLOSEST_ULL(tmp, NSEC_PER_SEC);
	if (clock_unit <= PWM_IMX_TPM_MOD_MOD)
		prescale = 0;
	else
		prescale = ilog2(clock_unit) + 1 - PWM_IMX_TPM_MOD_WIDTH;

	if ((!FIELD_FIT(PWM_IMX_TPM_SC_PS, prescale)))
		return -ERANGE;
	p->prescale = prescale;

	period_count = (clock_unit + ((1 << prescale) >> 1)) >> prescale;
	p->mod = period_count;

	/* calculate real period HW can support */
	tmp = (u64)period_count << prescale;
	tmp *= NSEC_PER_SEC;
	real_state->period = DIV_ROUND_CLOSEST_ULL(tmp, rate);

	/*
	 * if eventually the PWM output is inactive, either
	 * duty cycle is 0 or status is disabled, need to
	 * make sure the output pin is inactive.
	 */
	if (!state->enabled)
		real_state->duty_cycle = 0;
	else
		real_state->duty_cycle = state->duty_cycle;

	tmp = (u64)p->mod * real_state->duty_cycle;
	p->val = DIV_ROUND_CLOSEST_ULL(tmp, real_state->period);

	real_state->polarity = state->polarity;
	real_state->enabled = state->enabled;

	return 0;
}