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
struct zx_pwm_chip {int /*<<< orphan*/  wclk; } ;
struct pwm_device {int /*<<< orphan*/  hwpwm; } ;
struct pwm_chip {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 
 unsigned int NSEC_PER_SEC ; 
 int /*<<< orphan*/  ZX_PWM_CLKDIV (unsigned int) ; 
 int /*<<< orphan*/  ZX_PWM_CLKDIV_MASK ; 
 unsigned int ZX_PWM_CLKDIV_MAX ; 
 int /*<<< orphan*/  ZX_PWM_DUTY ; 
 int /*<<< orphan*/  ZX_PWM_EN ; 
 int /*<<< orphan*/  ZX_PWM_MODE ; 
 int /*<<< orphan*/  ZX_PWM_PERIOD ; 
 unsigned long long ZX_PWM_PERIOD_MAX ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (unsigned long long,unsigned int) ; 
 scalar_t__ pwm_is_enabled (struct pwm_device*) ; 
 struct zx_pwm_chip* to_zx_pwm_chip (struct pwm_chip*) ; 
 int /*<<< orphan*/  zx_pwm_set_mask (struct zx_pwm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zx_pwm_writel (struct zx_pwm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int zx_pwm_config(struct pwm_chip *chip, struct pwm_device *pwm,
			 unsigned int duty_ns, unsigned int period_ns)
{
	struct zx_pwm_chip *zpc = to_zx_pwm_chip(chip);
	unsigned int period_cycles, duty_cycles;
	unsigned long long c;
	unsigned int div = 1;
	unsigned long rate;

	/* Find out the best divider */
	rate = clk_get_rate(zpc->wclk);

	while (1) {
		c = rate / div;
		c = c * period_ns;
		do_div(c, NSEC_PER_SEC);

		if (c < ZX_PWM_PERIOD_MAX)
			break;

		div++;

		if (div > ZX_PWM_CLKDIV_MAX)
			return -ERANGE;
	}

	/* Calculate duty cycles */
	period_cycles = c;
	c *= duty_ns;
	do_div(c, period_ns);
	duty_cycles = c;

	/*
	 * If the PWM is being enabled, we have to temporarily disable it
	 * before configuring the registers.
	 */
	if (pwm_is_enabled(pwm))
		zx_pwm_set_mask(zpc, pwm->hwpwm, ZX_PWM_MODE, ZX_PWM_EN, 0);

	/* Set up registers */
	zx_pwm_set_mask(zpc, pwm->hwpwm, ZX_PWM_MODE, ZX_PWM_CLKDIV_MASK,
			ZX_PWM_CLKDIV(div));
	zx_pwm_writel(zpc, pwm->hwpwm, ZX_PWM_PERIOD, period_cycles);
	zx_pwm_writel(zpc, pwm->hwpwm, ZX_PWM_DUTY, duty_cycles);

	/* Re-enable the PWM if needed */
	if (pwm_is_enabled(pwm))
		zx_pwm_set_mask(zpc, pwm->hwpwm, ZX_PWM_MODE,
				ZX_PWM_EN, ZX_PWM_EN);

	return 0;
}