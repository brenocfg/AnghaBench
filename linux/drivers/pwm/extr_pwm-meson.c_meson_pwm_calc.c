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
typedef  unsigned long u64 ;
struct pwm_state {unsigned int duty_cycle; unsigned int period; scalar_t__ polarity; } ;
struct pwm_device {int dummy; } ;
struct meson_pwm_channel {unsigned int pre_div; unsigned int hi; unsigned int lo; int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct meson_pwm {TYPE_1__ chip; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int MISC_CLK_DIV_MASK ; 
 int NSEC_PER_SEC ; 
 scalar_t__ PWM_POLARITY_INVERSED ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int div64_u64 (unsigned long,int) ; 
 struct meson_pwm_channel* pwm_get_chip_data (struct pwm_device*) ; 

__attribute__((used)) static int meson_pwm_calc(struct meson_pwm *meson, struct pwm_device *pwm,
			  const struct pwm_state *state)
{
	struct meson_pwm_channel *channel = pwm_get_chip_data(pwm);
	unsigned int duty, period, pre_div, cnt, duty_cnt;
	unsigned long fin_freq = -1;

	duty = state->duty_cycle;
	period = state->period;

	if (state->polarity == PWM_POLARITY_INVERSED)
		duty = period - duty;

	fin_freq = clk_get_rate(channel->clk);
	if (fin_freq == 0) {
		dev_err(meson->chip.dev, "invalid source clock frequency\n");
		return -EINVAL;
	}

	dev_dbg(meson->chip.dev, "fin_freq: %lu Hz\n", fin_freq);

	pre_div = div64_u64(fin_freq * (u64)period, NSEC_PER_SEC * 0xffffLL);
	if (pre_div > MISC_CLK_DIV_MASK) {
		dev_err(meson->chip.dev, "unable to get period pre_div\n");
		return -EINVAL;
	}

	cnt = div64_u64(fin_freq * (u64)period, NSEC_PER_SEC * (pre_div + 1));
	if (cnt > 0xffff) {
		dev_err(meson->chip.dev, "unable to get period cnt\n");
		return -EINVAL;
	}

	dev_dbg(meson->chip.dev, "period=%u pre_div=%u cnt=%u\n", period,
		pre_div, cnt);

	if (duty == period) {
		channel->pre_div = pre_div;
		channel->hi = cnt;
		channel->lo = 0;
	} else if (duty == 0) {
		channel->pre_div = pre_div;
		channel->hi = 0;
		channel->lo = cnt;
	} else {
		/* Then check is we can have the duty with the same pre_div */
		duty_cnt = div64_u64(fin_freq * (u64)duty,
				     NSEC_PER_SEC * (pre_div + 1));
		if (duty_cnt > 0xffff) {
			dev_err(meson->chip.dev, "unable to get duty cycle\n");
			return -EINVAL;
		}

		dev_dbg(meson->chip.dev, "duty=%u pre_div=%u duty_cnt=%u\n",
			duty, pre_div, duty_cnt);

		channel->pre_div = pre_div;
		channel->hi = duty_cnt;
		channel->lo = cnt - duty_cnt;
	}

	return 0;
}