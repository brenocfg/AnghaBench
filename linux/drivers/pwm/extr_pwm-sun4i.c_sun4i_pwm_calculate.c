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
typedef  int u32 ;
struct sun4i_pwm_chip {TYPE_1__* data; int /*<<< orphan*/  clk; } ;
struct pwm_state {int period; int duty_cycle; } ;
struct TYPE_2__ {scalar_t__ has_prescaler_bypass; } ;

/* Variables and functions */
 int EINVAL ; 
 int NSEC_PER_SEC ; 
 int PWM_PRD_MASK ; 
 unsigned int PWM_PRESCAL_MASK ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 unsigned int* prescaler_table ; 

__attribute__((used)) static int sun4i_pwm_calculate(struct sun4i_pwm_chip *sun4i_pwm,
			       const struct pwm_state *state,
			       u32 *dty, u32 *prd, unsigned int *prsclr)
{
	u64 clk_rate, div = 0;
	unsigned int pval, prescaler = 0;

	clk_rate = clk_get_rate(sun4i_pwm->clk);

	if (sun4i_pwm->data->has_prescaler_bypass) {
		/* First, test without any prescaler when available */
		prescaler = PWM_PRESCAL_MASK;
		pval = 1;
		/*
		 * When not using any prescaler, the clock period in nanoseconds
		 * is not an integer so round it half up instead of
		 * truncating to get less surprising values.
		 */
		div = clk_rate * state->period + NSEC_PER_SEC / 2;
		do_div(div, NSEC_PER_SEC);
		if (div - 1 > PWM_PRD_MASK)
			prescaler = 0;
	}

	if (prescaler == 0) {
		/* Go up from the first divider */
		for (prescaler = 0; prescaler < PWM_PRESCAL_MASK; prescaler++) {
			if (!prescaler_table[prescaler])
				continue;
			pval = prescaler_table[prescaler];
			div = clk_rate;
			do_div(div, pval);
			div = div * state->period;
			do_div(div, NSEC_PER_SEC);
			if (div - 1 <= PWM_PRD_MASK)
				break;
		}

		if (div - 1 > PWM_PRD_MASK)
			return -EINVAL;
	}

	*prd = div;
	div *= state->duty_cycle;
	do_div(div, state->period);
	*dty = div;
	*prsclr = prescaler;

	return 0;
}