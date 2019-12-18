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
typedef  scalar_t__ u32 ;
struct sprd_pwm_chn {scalar_t__ clk_rate; } ;
struct sprd_pwm_chip {struct sprd_pwm_chn* chn; } ;
struct pwm_device {size_t hwpwm; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_CLOSEST_ULL (int,int) ; 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 int /*<<< orphan*/  SPRD_PWM_DUTY ; 
 int /*<<< orphan*/  SPRD_PWM_MOD ; 
 int SPRD_PWM_MOD_MAX ; 
 int /*<<< orphan*/  SPRD_PWM_PRESCALE ; 
 scalar_t__ SPRD_PWM_PRESCALE_MSK ; 
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprd_pwm_write (struct sprd_pwm_chip*,size_t,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sprd_pwm_config(struct sprd_pwm_chip *spc, struct pwm_device *pwm,
			   int duty_ns, int period_ns)
{
	struct sprd_pwm_chn *chn = &spc->chn[pwm->hwpwm];
	u32 prescale, duty;
	u64 tmp;

	/*
	 * The hardware provides a counter that is feed by the source clock.
	 * The period length is (PRESCALE + 1) * MOD counter steps.
	 * The duty cycle length is (PRESCALE + 1) * DUTY counter steps.
	 *
	 * To keep the maths simple we're always using MOD = SPRD_PWM_MOD_MAX.
	 * The value for PRESCALE is selected such that the resulting period
	 * gets the maximal length not bigger than the requested one with the
	 * given settings (MOD = SPRD_PWM_MOD_MAX and input clock).
	 */
	duty = duty_ns * SPRD_PWM_MOD_MAX / period_ns;

	tmp = (u64)chn->clk_rate * period_ns;
	do_div(tmp, NSEC_PER_SEC);
	prescale = DIV_ROUND_CLOSEST_ULL(tmp, SPRD_PWM_MOD_MAX) - 1;
	if (prescale > SPRD_PWM_PRESCALE_MSK)
		prescale = SPRD_PWM_PRESCALE_MSK;

	/*
	 * Note: Writing DUTY triggers the hardware to actually apply the
	 * values written to MOD and DUTY to the output, so must keep writing
	 * DUTY last.
	 *
	 * The hardware can ensures that current running period is completed
	 * before changing a new configuration to avoid mixed settings.
	 */
	sprd_pwm_write(spc, pwm->hwpwm, SPRD_PWM_PRESCALE, prescale);
	sprd_pwm_write(spc, pwm->hwpwm, SPRD_PWM_MOD, SPRD_PWM_MOD_MAX);
	sprd_pwm_write(spc, pwm->hwpwm, SPRD_PWM_DUTY, duty);

	return 0;
}