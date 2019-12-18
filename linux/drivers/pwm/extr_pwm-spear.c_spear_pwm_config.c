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
struct spear_pwm_chip {int /*<<< orphan*/  clk; } ;
struct pwm_device {int /*<<< orphan*/  hwpwm; } ;
struct pwm_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PWMCR ; 
 unsigned long PWMCR_MAX_PRESCALE ; 
 unsigned long PWMCR_MIN_PRESCALE ; 
 unsigned long PWMCR_PRESCALE_SHIFT ; 
 int /*<<< orphan*/  PWMDCR ; 
 unsigned long PWMDCR_MAX_DUTY ; 
 unsigned long PWMDCR_MIN_DUTY ; 
 int /*<<< orphan*/  PWMPCR ; 
 unsigned long PWMPCR_MAX_PERIOD ; 
 unsigned long PWMPCR_MIN_PERIOD ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 unsigned long div64_u64 (int,int) ; 
 int /*<<< orphan*/  spear_pwm_writel (struct spear_pwm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 struct spear_pwm_chip* to_spear_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static int spear_pwm_config(struct pwm_chip *chip, struct pwm_device *pwm,
			    int duty_ns, int period_ns)
{
	struct spear_pwm_chip *pc = to_spear_pwm_chip(chip);
	u64 val, div, clk_rate;
	unsigned long prescale = PWMCR_MIN_PRESCALE, pv, dc;
	int ret;

	/*
	 * Find pv, dc and prescale to suit duty_ns and period_ns. This is done
	 * according to formulas described below:
	 *
	 * period_ns = 10^9 * (PRESCALE + 1) * PV / PWM_CLK_RATE
	 * duty_ns = 10^9 * (PRESCALE + 1) * DC / PWM_CLK_RATE
	 *
	 * PV = (PWM_CLK_RATE * period_ns) / (10^9 * (PRESCALE + 1))
	 * DC = (PWM_CLK_RATE * duty_ns) / (10^9 * (PRESCALE + 1))
	 */
	clk_rate = clk_get_rate(pc->clk);
	while (1) {
		div = 1000000000;
		div *= 1 + prescale;
		val = clk_rate * period_ns;
		pv = div64_u64(val, div);
		val = clk_rate * duty_ns;
		dc = div64_u64(val, div);

		/* if duty_ns and period_ns are not achievable then return */
		if (pv < PWMPCR_MIN_PERIOD || dc < PWMDCR_MIN_DUTY)
			return -EINVAL;

		/*
		 * if pv and dc have crossed their upper limit, then increase
		 * prescale and recalculate pv and dc.
		 */
		if (pv > PWMPCR_MAX_PERIOD || dc > PWMDCR_MAX_DUTY) {
			if (++prescale > PWMCR_MAX_PRESCALE)
				return -EINVAL;
			continue;
		}
		break;
	}

	/*
	 * NOTE: the clock to PWM has to be enabled first before writing to the
	 * registers.
	 */
	ret = clk_enable(pc->clk);
	if (ret)
		return ret;

	spear_pwm_writel(pc, pwm->hwpwm, PWMCR,
			prescale << PWMCR_PRESCALE_SHIFT);
	spear_pwm_writel(pc, pwm->hwpwm, PWMDCR, dc);
	spear_pwm_writel(pc, pwm->hwpwm, PWMPCR, pv);
	clk_disable(pc->clk);

	return 0;
}