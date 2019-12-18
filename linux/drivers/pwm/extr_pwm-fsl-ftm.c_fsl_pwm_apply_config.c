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
typedef  scalar_t__ u32 ;
struct pwm_state {scalar_t__ polarity; int /*<<< orphan*/  duty_cycle; int /*<<< orphan*/  period; } ;
struct pwm_device {int /*<<< orphan*/  hwpwm; } ;
struct fsl_pwm_periodcfg {scalar_t__ clk_select; unsigned int mod_period; scalar_t__ clk_ps; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct fsl_pwm_chip {int /*<<< orphan*/  regmap; struct fsl_pwm_periodcfg period; int /*<<< orphan*/ * clk; TYPE_1__ chip; } ;
typedef  enum fsl_pwm_clk { ____Placeholder_fsl_pwm_clk } fsl_pwm_clk ;

/* Variables and functions */
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  FTM_CSC (int /*<<< orphan*/ ) ; 
 unsigned int FTM_CSC_ELSB ; 
 unsigned int FTM_CSC_MSB ; 
 int /*<<< orphan*/  FTM_CV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTM_MOD ; 
 int /*<<< orphan*/  FTM_POL ; 
 int /*<<< orphan*/  FTM_SC ; 
 scalar_t__ FTM_SC_CLK (int) ; 
 scalar_t__ FTM_SC_CLK_MASK ; 
 scalar_t__ FTM_SC_PS_MASK ; 
 scalar_t__ PWM_POLARITY_INVERSED ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 unsigned int fsl_pwm_calculate_duty (struct fsl_pwm_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_pwm_calculate_period (struct fsl_pwm_chip*,int /*<<< orphan*/ ,struct fsl_pwm_periodcfg*) ; 
 int /*<<< orphan*/  fsl_pwm_is_any_pwm_enabled (struct fsl_pwm_chip*,struct pwm_device*) ; 
 scalar_t__ fsl_pwm_is_other_pwm_enabled (struct fsl_pwm_chip*,struct pwm_device*) ; 
 int /*<<< orphan*/  fsl_pwm_periodcfg_are_equal (struct fsl_pwm_periodcfg*,struct fsl_pwm_periodcfg*) ; 
 int /*<<< orphan*/  ftm_clear_write_protection (struct fsl_pwm_chip*) ; 
 int /*<<< orphan*/  ftm_set_write_protection (struct fsl_pwm_chip*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int fsl_pwm_apply_config(struct fsl_pwm_chip *fpc,
				struct pwm_device *pwm,
				const struct pwm_state *newstate)
{
	unsigned int duty;
	u32 reg_polarity;

	struct fsl_pwm_periodcfg periodcfg;
	bool do_write_period = false;

	if (!fsl_pwm_calculate_period(fpc, newstate->period, &periodcfg)) {
		dev_err(fpc->chip.dev, "failed to calculate new period\n");
		return -EINVAL;
	}

	if (!fsl_pwm_is_any_pwm_enabled(fpc, pwm))
		do_write_period = true;
	/*
	 * The Freescale FTM controller supports only a single period for
	 * all PWM channels, therefore verify if the newly computed period
	 * is different than the current period being used. In such case
	 * we allow to change the period only if no other pwm is running.
	 */
	else if (!fsl_pwm_periodcfg_are_equal(&fpc->period, &periodcfg)) {
		if (fsl_pwm_is_other_pwm_enabled(fpc, pwm)) {
			dev_err(fpc->chip.dev,
				"Cannot change period for PWM %u, disable other PWMs first\n",
				pwm->hwpwm);
			return -EBUSY;
		}
		if (fpc->period.clk_select != periodcfg.clk_select) {
			int ret;
			enum fsl_pwm_clk oldclk = fpc->period.clk_select;
			enum fsl_pwm_clk newclk = periodcfg.clk_select;

			ret = clk_prepare_enable(fpc->clk[newclk]);
			if (ret)
				return ret;
			clk_disable_unprepare(fpc->clk[oldclk]);
		}
		do_write_period = true;
	}

	ftm_clear_write_protection(fpc);

	if (do_write_period) {
		regmap_update_bits(fpc->regmap, FTM_SC, FTM_SC_CLK_MASK,
				   FTM_SC_CLK(periodcfg.clk_select));
		regmap_update_bits(fpc->regmap, FTM_SC, FTM_SC_PS_MASK,
				   periodcfg.clk_ps);
		regmap_write(fpc->regmap, FTM_MOD, periodcfg.mod_period);

		fpc->period = periodcfg;
	}

	duty = fsl_pwm_calculate_duty(fpc, newstate->duty_cycle);

	regmap_write(fpc->regmap, FTM_CSC(pwm->hwpwm),
		     FTM_CSC_MSB | FTM_CSC_ELSB);
	regmap_write(fpc->regmap, FTM_CV(pwm->hwpwm), duty);

	reg_polarity = 0;
	if (newstate->polarity == PWM_POLARITY_INVERSED)
		reg_polarity = BIT(pwm->hwpwm);

	regmap_update_bits(fpc->regmap, FTM_POL, BIT(pwm->hwpwm), reg_polarity);

	ftm_set_write_protection(fpc);

	return 0;
}