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
typedef  unsigned int u32 ;
struct pwm_device {unsigned int hwpwm; } ;
struct pwm_chip {int dummy; } ;
struct brcmstb_pwm {int /*<<< orphan*/  lock; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 unsigned long CONST_VAR_F_MAX ; 
 unsigned long CONST_VAR_F_MIN ; 
 unsigned int CTRL2_OUT_SELECT ; 
 unsigned int CTRL_CHAN_OFFS ; 
 int CWORD_BIT_SIZE ; 
 int EINVAL ; 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  PWM_CTRL2 ; 
 int /*<<< orphan*/  PWM_CWORD_LSB (unsigned int) ; 
 int /*<<< orphan*/  PWM_CWORD_MSB (unsigned int) ; 
 int /*<<< orphan*/  PWM_ON (unsigned int) ; 
 unsigned long PWM_ON_MIN ; 
 int PWM_ON_PERIOD_MAX ; 
 int /*<<< orphan*/  PWM_PERIOD (unsigned int) ; 
 unsigned long PWM_PERIOD_MIN ; 
 unsigned int brcmstb_pwm_readl (struct brcmstb_pwm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmstb_pwm_writel (struct brcmstb_pwm*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct brcmstb_pwm* to_brcmstb_pwm (struct pwm_chip*) ; 

__attribute__((used)) static int brcmstb_pwm_config(struct pwm_chip *chip, struct pwm_device *pwm,
			      int duty_ns, int period_ns)
{
	struct brcmstb_pwm *p = to_brcmstb_pwm(chip);
	unsigned long pc, dc, cword = CONST_VAR_F_MAX;
	unsigned int channel = pwm->hwpwm;
	u32 value;

	/*
	 * If asking for a duty_ns equal to period_ns, we need to substract
	 * the period value by 1 to make it shorter than the "on" time and
	 * produce a flat 100% duty cycle signal, and max out the "on" time
	 */
	if (duty_ns == period_ns) {
		dc = PWM_ON_PERIOD_MAX;
		pc = PWM_ON_PERIOD_MAX - 1;
		goto done;
	}

	while (1) {
		u64 rate, tmp;

		/*
		 * Calculate the base rate from base frequency and current
		 * cword
		 */
		rate = (u64)clk_get_rate(p->clk) * (u64)cword;
		do_div(rate, 1 << CWORD_BIT_SIZE);

		tmp = period_ns * rate;
		do_div(tmp, NSEC_PER_SEC);
		pc = tmp;

		tmp = (duty_ns + 1) * rate;
		do_div(tmp, NSEC_PER_SEC);
		dc = tmp;

		/*
		 * We can be called with separate duty and period updates,
		 * so do not reject dc == 0 right away
		 */
		if (pc == PWM_PERIOD_MIN || (dc < PWM_ON_MIN && duty_ns))
			return -EINVAL;

		/* We converged on a calculation */
		if (pc <= PWM_ON_PERIOD_MAX && dc <= PWM_ON_PERIOD_MAX)
			break;

		/*
		 * The cword needs to be a power of 2 for the variable
		 * frequency generator to output a 50% duty cycle variable
		 * frequency which is used as input clock to the fixed
		 * frequency generator.
		 */
		cword >>= 1;

		/*
		 * Desired periods are too large, we do not have a divider
		 * for them
		 */
		if (cword < CONST_VAR_F_MIN)
			return -EINVAL;
	}

done:
	/*
	 * Configure the defined "cword" value to have the variable frequency
	 * generator output a base frequency for the constant frequency
	 * generator to derive from.
	 */
	spin_lock(&p->lock);
	brcmstb_pwm_writel(p, cword >> 8, PWM_CWORD_MSB(channel));
	brcmstb_pwm_writel(p, cword & 0xff, PWM_CWORD_LSB(channel));

	/* Select constant frequency signal output */
	value = brcmstb_pwm_readl(p, PWM_CTRL2);
	value |= CTRL2_OUT_SELECT << (channel * CTRL_CHAN_OFFS);
	brcmstb_pwm_writel(p, value, PWM_CTRL2);

	/* Configure on and period value */
	brcmstb_pwm_writel(p, pc, PWM_PERIOD(channel));
	brcmstb_pwm_writel(p, dc, PWM_ON(channel));
	spin_unlock(&p->lock);

	return 0;
}