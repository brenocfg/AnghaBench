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
typedef  int u32 ;
struct pwm_device {int /*<<< orphan*/  hwpwm; } ;
struct pwm_chip {int /*<<< orphan*/  dev; } ;
struct img_pwm_chip {int min_period_ns; int max_period_ns; int /*<<< orphan*/  pwm_clk; TYPE_1__* data; } ;
struct TYPE_2__ {unsigned int max_timebase; } ;

/* Variables and functions */
 void* DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
 int ERANGE ; 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  PWM_CH_CFG (int /*<<< orphan*/ ) ; 
 int PWM_CH_CFG_DUTY_SHIFT ; 
 int PWM_CH_CFG_TMBASE_SHIFT ; 
 int /*<<< orphan*/  PWM_CTRL_CFG ; 
 int PWM_CTRL_CFG_DIV_MASK ; 
 int PWM_CTRL_CFG_DIV_SHIFT (int /*<<< orphan*/ ) ; 
 int PWM_CTRL_CFG_NO_SUB_DIV ; 
 int PWM_CTRL_CFG_SUB_DIV0 ; 
 int PWM_CTRL_CFG_SUB_DIV0_DIV1 ; 
 int PWM_CTRL_CFG_SUB_DIV1 ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int img_pwm_readl (struct img_pwm_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_pwm_writel (struct img_pwm_chip*,int /*<<< orphan*/ ,int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 struct img_pwm_chip* to_img_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static int img_pwm_config(struct pwm_chip *chip, struct pwm_device *pwm,
			  int duty_ns, int period_ns)
{
	u32 val, div, duty, timebase;
	unsigned long mul, output_clk_hz, input_clk_hz;
	struct img_pwm_chip *pwm_chip = to_img_pwm_chip(chip);
	unsigned int max_timebase = pwm_chip->data->max_timebase;
	int ret;

	if (period_ns < pwm_chip->min_period_ns ||
	    period_ns > pwm_chip->max_period_ns) {
		dev_err(chip->dev, "configured period not in range\n");
		return -ERANGE;
	}

	input_clk_hz = clk_get_rate(pwm_chip->pwm_clk);
	output_clk_hz = DIV_ROUND_UP(NSEC_PER_SEC, period_ns);

	mul = DIV_ROUND_UP(input_clk_hz, output_clk_hz);
	if (mul <= max_timebase) {
		div = PWM_CTRL_CFG_NO_SUB_DIV;
		timebase = DIV_ROUND_UP(mul, 1);
	} else if (mul <= max_timebase * 8) {
		div = PWM_CTRL_CFG_SUB_DIV0;
		timebase = DIV_ROUND_UP(mul, 8);
	} else if (mul <= max_timebase * 64) {
		div = PWM_CTRL_CFG_SUB_DIV1;
		timebase = DIV_ROUND_UP(mul, 64);
	} else if (mul <= max_timebase * 512) {
		div = PWM_CTRL_CFG_SUB_DIV0_DIV1;
		timebase = DIV_ROUND_UP(mul, 512);
	} else {
		dev_err(chip->dev,
			"failed to configure timebase steps/divider value\n");
		return -EINVAL;
	}

	duty = DIV_ROUND_UP(timebase * duty_ns, period_ns);

	ret = pm_runtime_get_sync(chip->dev);
	if (ret < 0)
		return ret;

	val = img_pwm_readl(pwm_chip, PWM_CTRL_CFG);
	val &= ~(PWM_CTRL_CFG_DIV_MASK << PWM_CTRL_CFG_DIV_SHIFT(pwm->hwpwm));
	val |= (div & PWM_CTRL_CFG_DIV_MASK) <<
		PWM_CTRL_CFG_DIV_SHIFT(pwm->hwpwm);
	img_pwm_writel(pwm_chip, PWM_CTRL_CFG, val);

	val = (duty << PWM_CH_CFG_DUTY_SHIFT) |
	      (timebase << PWM_CH_CFG_TMBASE_SHIFT);
	img_pwm_writel(pwm_chip, PWM_CH_CFG(pwm->hwpwm), val);

	pm_runtime_mark_last_busy(chip->dev);
	pm_runtime_put_autosuspend(chip->dev);

	return 0;
}