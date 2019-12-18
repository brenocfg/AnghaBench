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
struct sti_pwm_chip {int /*<<< orphan*/  sti_pwm_lock; int /*<<< orphan*/  en_count; int /*<<< orphan*/  pwm_out_en; int /*<<< orphan*/  cpt_clk; int /*<<< orphan*/  pwm_clk; struct device* dev; } ;
struct pwm_device {int /*<<< orphan*/  hwpwm; } ;
struct pwm_chip {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_field_write (int /*<<< orphan*/ ,int) ; 
 struct sti_pwm_chip* to_sti_pwmchip (struct pwm_chip*) ; 

__attribute__((used)) static int sti_pwm_enable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct sti_pwm_chip *pc = to_sti_pwmchip(chip);
	struct device *dev = pc->dev;
	int ret = 0;

	/*
	 * Since we have a common enable for all PWM devices, do not enable if
	 * already enabled.
	 */
	mutex_lock(&pc->sti_pwm_lock);

	if (!pc->en_count) {
		ret = clk_enable(pc->pwm_clk);
		if (ret)
			goto out;

		ret = clk_enable(pc->cpt_clk);
		if (ret)
			goto out;

		ret = regmap_field_write(pc->pwm_out_en, 1);
		if (ret) {
			dev_err(dev, "failed to enable PWM device %u: %d\n",
				pwm->hwpwm, ret);
			goto out;
		}
	}

	pc->en_count++;

out:
	mutex_unlock(&pc->sti_pwm_lock);
	return ret;
}