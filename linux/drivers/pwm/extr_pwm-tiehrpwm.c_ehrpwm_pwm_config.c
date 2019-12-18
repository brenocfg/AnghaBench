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
typedef  int u32 ;
typedef  int u16 ;
struct pwm_device {unsigned int hwpwm; } ;
struct pwm_chip {int /*<<< orphan*/  dev; } ;
struct ehrpwm_pwm_chip {unsigned long long clk_rate; int* period_cycles; int /*<<< orphan*/  mmio_base; } ;

/* Variables and functions */
 unsigned int CMPA ; 
 unsigned int CMPB ; 
 int EINVAL ; 
 int ERANGE ; 
 int NSEC_PER_SEC ; 
 unsigned int NUM_PWM_CHANNEL ; 
 int PERIOD_MAX ; 
 int /*<<< orphan*/  TBCTL ; 
 int /*<<< orphan*/  TBCTL_CLKDIV_MASK ; 
 int /*<<< orphan*/  TBCTL_CTRMODE_MASK ; 
 int TBCTL_CTRMODE_UP ; 
 int /*<<< orphan*/  TBCTL_PRDLD_MASK ; 
 int TBCTL_PRDLD_SHDW ; 
 unsigned int TBPRD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 
 int /*<<< orphan*/  ehrpwm_modify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ehrpwm_write (int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ set_prescale_div (int,int*,int*) ; 
 struct ehrpwm_pwm_chip* to_ehrpwm_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static int ehrpwm_pwm_config(struct pwm_chip *chip, struct pwm_device *pwm,
			     int duty_ns, int period_ns)
{
	struct ehrpwm_pwm_chip *pc = to_ehrpwm_pwm_chip(chip);
	u32 period_cycles, duty_cycles;
	u16 ps_divval, tb_divval;
	unsigned int i, cmp_reg;
	unsigned long long c;

	if (period_ns > NSEC_PER_SEC)
		return -ERANGE;

	c = pc->clk_rate;
	c = c * period_ns;
	do_div(c, NSEC_PER_SEC);
	period_cycles = (unsigned long)c;

	if (period_cycles < 1) {
		period_cycles = 1;
		duty_cycles = 1;
	} else {
		c = pc->clk_rate;
		c = c * duty_ns;
		do_div(c, NSEC_PER_SEC);
		duty_cycles = (unsigned long)c;
	}

	/*
	 * Period values should be same for multiple PWM channels as IP uses
	 * same period register for multiple channels.
	 */
	for (i = 0; i < NUM_PWM_CHANNEL; i++) {
		if (pc->period_cycles[i] &&
				(pc->period_cycles[i] != period_cycles)) {
			/*
			 * Allow channel to reconfigure period if no other
			 * channels being configured.
			 */
			if (i == pwm->hwpwm)
				continue;

			dev_err(chip->dev,
				"period value conflicts with channel %u\n",
				i);
			return -EINVAL;
		}
	}

	pc->period_cycles[pwm->hwpwm] = period_cycles;

	/* Configure clock prescaler to support Low frequency PWM wave */
	if (set_prescale_div(period_cycles/PERIOD_MAX, &ps_divval,
			     &tb_divval)) {
		dev_err(chip->dev, "Unsupported values\n");
		return -EINVAL;
	}

	pm_runtime_get_sync(chip->dev);

	/* Update clock prescaler values */
	ehrpwm_modify(pc->mmio_base, TBCTL, TBCTL_CLKDIV_MASK, tb_divval);

	/* Update period & duty cycle with presacler division */
	period_cycles = period_cycles / ps_divval;
	duty_cycles = duty_cycles / ps_divval;

	/* Configure shadow loading on Period register */
	ehrpwm_modify(pc->mmio_base, TBCTL, TBCTL_PRDLD_MASK, TBCTL_PRDLD_SHDW);

	ehrpwm_write(pc->mmio_base, TBPRD, period_cycles);

	/* Configure ehrpwm counter for up-count mode */
	ehrpwm_modify(pc->mmio_base, TBCTL, TBCTL_CTRMODE_MASK,
		      TBCTL_CTRMODE_UP);

	if (pwm->hwpwm == 1)
		/* Channel 1 configured with compare B register */
		cmp_reg = CMPB;
	else
		/* Channel 0 configured with compare A register */
		cmp_reg = CMPA;

	ehrpwm_write(pc->mmio_base, cmp_reg, duty_cycles);

	pm_runtime_put_sync(chip->dev);

	return 0;
}