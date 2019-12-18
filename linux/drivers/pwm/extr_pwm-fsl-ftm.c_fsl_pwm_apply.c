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
struct pwm_state {scalar_t__ enabled; } ;
struct pwm_device {int /*<<< orphan*/  hwpwm; struct pwm_state state; } ;
struct pwm_chip {int dummy; } ;
struct TYPE_2__ {size_t clk_select; } ;
struct fsl_pwm_chip {int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; TYPE_1__ period; int /*<<< orphan*/ * clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 size_t FSL_PWM_CLK_CNTEN ; 
 int /*<<< orphan*/  FTM_OUTMASK ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int fsl_pwm_apply_config (struct fsl_pwm_chip*,struct pwm_device*,struct pwm_state const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fsl_pwm_chip* to_fsl_chip (struct pwm_chip*) ; 

__attribute__((used)) static int fsl_pwm_apply(struct pwm_chip *chip, struct pwm_device *pwm,
			 const struct pwm_state *newstate)
{
	struct fsl_pwm_chip *fpc = to_fsl_chip(chip);
	struct pwm_state *oldstate = &pwm->state;
	int ret = 0;

	/*
	 * oldstate to newstate : action
	 *
	 * disabled to disabled : ignore
	 * enabled to disabled : disable
	 * enabled to enabled : update settings
	 * disabled to enabled : update settings + enable
	 */

	mutex_lock(&fpc->lock);

	if (!newstate->enabled) {
		if (oldstate->enabled) {
			regmap_update_bits(fpc->regmap, FTM_OUTMASK,
					   BIT(pwm->hwpwm), BIT(pwm->hwpwm));
			clk_disable_unprepare(fpc->clk[FSL_PWM_CLK_CNTEN]);
			clk_disable_unprepare(fpc->clk[fpc->period.clk_select]);
		}

		goto end_mutex;
	}

	ret = fsl_pwm_apply_config(fpc, pwm, newstate);
	if (ret)
		goto end_mutex;

	/* check if need to enable */
	if (!oldstate->enabled) {
		ret = clk_prepare_enable(fpc->clk[fpc->period.clk_select]);
		if (ret)
			goto end_mutex;

		ret = clk_prepare_enable(fpc->clk[FSL_PWM_CLK_CNTEN]);
		if (ret) {
			clk_disable_unprepare(fpc->clk[fpc->period.clk_select]);
			goto end_mutex;
		}

		regmap_update_bits(fpc->regmap, FTM_OUTMASK, BIT(pwm->hwpwm),
				   0);
	}

end_mutex:
	mutex_unlock(&fpc->lock);
	return ret;
}