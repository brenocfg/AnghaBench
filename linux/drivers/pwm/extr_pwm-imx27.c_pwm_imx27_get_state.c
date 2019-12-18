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
typedef  int u32 ;
struct pwm_state {int enabled; void* duty_cycle; void* period; int /*<<< orphan*/  polarity; } ;
struct pwm_imx27_chip {scalar_t__ mmio_base; int /*<<< orphan*/  clk_per; } ;
struct pwm_device {int dummy; } ;
struct pwm_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* DIV_ROUND_CLOSEST_ULL (int,int) ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 scalar_t__ MX3_PWMCR ; 
 int MX3_PWMCR_EN ; 
 int /*<<< orphan*/  MX3_PWMCR_POUTC ; 
#define  MX3_PWMCR_POUTC_INVERTED 129 
#define  MX3_PWMCR_POUTC_NORMAL 128 
 int MX3_PWMCR_PRESCALER_GET (int) ; 
 scalar_t__ MX3_PWMPR ; 
 int MX3_PWMPR_MAX ; 
 scalar_t__ MX3_PWMSAR ; 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  PWM_POLARITY_INVERSED ; 
 int /*<<< orphan*/  PWM_POLARITY_NORMAL ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pwm_imx27_clk_disable_unprepare (struct pwm_chip*) ; 
 int pwm_imx27_clk_prepare_enable (struct pwm_chip*) ; 
 int readl (scalar_t__) ; 
 struct pwm_imx27_chip* to_pwm_imx27_chip (struct pwm_chip*) ; 

__attribute__((used)) static void pwm_imx27_get_state(struct pwm_chip *chip,
				struct pwm_device *pwm, struct pwm_state *state)
{
	struct pwm_imx27_chip *imx = to_pwm_imx27_chip(chip);
	u32 period, prescaler, pwm_clk, val;
	u64 tmp;
	int ret;

	ret = pwm_imx27_clk_prepare_enable(chip);
	if (ret < 0)
		return;

	val = readl(imx->mmio_base + MX3_PWMCR);

	if (val & MX3_PWMCR_EN)
		state->enabled = true;
	else
		state->enabled = false;

	switch (FIELD_GET(MX3_PWMCR_POUTC, val)) {
	case MX3_PWMCR_POUTC_NORMAL:
		state->polarity = PWM_POLARITY_NORMAL;
		break;
	case MX3_PWMCR_POUTC_INVERTED:
		state->polarity = PWM_POLARITY_INVERSED;
		break;
	default:
		dev_warn(chip->dev, "can't set polarity, output disconnected");
	}

	prescaler = MX3_PWMCR_PRESCALER_GET(val);
	pwm_clk = clk_get_rate(imx->clk_per);
	pwm_clk = DIV_ROUND_CLOSEST_ULL(pwm_clk, prescaler);
	val = readl(imx->mmio_base + MX3_PWMPR);
	period = val >= MX3_PWMPR_MAX ? MX3_PWMPR_MAX : val;

	/* PWMOUT (Hz) = PWMCLK / (PWMPR + 2) */
	tmp = NSEC_PER_SEC * (u64)(period + 2);
	state->period = DIV_ROUND_CLOSEST_ULL(tmp, pwm_clk);

	/* PWMSAR can be read only if PWM is enabled */
	if (state->enabled) {
		val = readl(imx->mmio_base + MX3_PWMSAR);
		tmp = NSEC_PER_SEC * (u64)(val);
		state->duty_cycle = DIV_ROUND_CLOSEST_ULL(tmp, pwm_clk);
	} else {
		state->duty_cycle = 0;
	}

	if (!state->enabled)
		pwm_imx27_clk_disable_unprepare(chip);
}