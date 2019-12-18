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
typedef  unsigned int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct pwm_state {scalar_t__ polarity; int enabled; unsigned int duty_cycle; scalar_t__ period; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct pwm_sifive_ddata {scalar_t__ approx_period; int user_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  clk; scalar_t__ regs; TYPE_1__ chip; } ;
struct pwm_device {int hwpwm; struct pwm_state state; } ;
struct pwm_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_CLOSEST_ULL (unsigned long long,scalar_t__) ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ PWM_POLARITY_INVERSED ; 
 unsigned int PWM_SIFIVE_CMPWIDTH ; 
 scalar_t__ PWM_SIFIVE_PWMCMP0 ; 
 int PWM_SIFIVE_SIZE_PWMCMP ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct pwm_sifive_ddata* pwm_sifive_chip_to_ddata (struct pwm_chip*) ; 
 int /*<<< orphan*/  pwm_sifive_enable (struct pwm_chip*,int) ; 
 int /*<<< orphan*/  pwm_sifive_update_clock (struct pwm_sifive_ddata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pwm_sifive_apply(struct pwm_chip *chip, struct pwm_device *pwm,
			    const struct pwm_state *state)
{
	struct pwm_sifive_ddata *ddata = pwm_sifive_chip_to_ddata(chip);
	struct pwm_state cur_state;
	unsigned int duty_cycle;
	unsigned long long num;
	bool enabled;
	int ret = 0;
	u32 frac;

	if (state->polarity != PWM_POLARITY_INVERSED)
		return -EINVAL;

	ret = clk_enable(ddata->clk);
	if (ret) {
		dev_err(ddata->chip.dev, "Enable clk failed\n");
		return ret;
	}

	mutex_lock(&ddata->lock);
	cur_state = pwm->state;
	enabled = cur_state.enabled;

	duty_cycle = state->duty_cycle;
	if (!state->enabled)
		duty_cycle = 0;

	/*
	 * The problem of output producing mixed setting as mentioned at top,
	 * occurs here. To minimize the window for this problem, we are
	 * calculating the register values first and then writing them
	 * consecutively
	 */
	num = (u64)duty_cycle * (1U << PWM_SIFIVE_CMPWIDTH);
	frac = DIV_ROUND_CLOSEST_ULL(num, state->period);
	/* The hardware cannot generate a 100% duty cycle */
	frac = min(frac, (1U << PWM_SIFIVE_CMPWIDTH) - 1);

	if (state->period != ddata->approx_period) {
		if (ddata->user_count != 1) {
			ret = -EBUSY;
			goto exit;
		}
		ddata->approx_period = state->period;
		pwm_sifive_update_clock(ddata, clk_get_rate(ddata->clk));
	}

	writel(frac, ddata->regs + PWM_SIFIVE_PWMCMP0 +
	       pwm->hwpwm * PWM_SIFIVE_SIZE_PWMCMP);

	if (state->enabled != enabled)
		pwm_sifive_enable(chip, state->enabled);

exit:
	clk_disable(ddata->clk);
	mutex_unlock(&ddata->lock);
	return ret;
}