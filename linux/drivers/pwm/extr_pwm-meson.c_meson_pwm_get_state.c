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
struct pwm_state {int enabled; void* duty_cycle; void* period; } ;
struct pwm_device {size_t hwpwm; } ;
struct pwm_chip {int dummy; } ;
struct meson_pwm_channel_data {int pwm_en_mask; int clk_en_mask; int clk_div_shift; scalar_t__ reg_offset; } ;
struct meson_pwm_channel {scalar_t__ lo; scalar_t__ hi; void* pre_div; } ;
struct meson_pwm {scalar_t__ base; struct meson_pwm_channel* channels; } ;

/* Variables and functions */
 void* FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MISC_CLK_DIV_MASK ; 
 int /*<<< orphan*/  PWM_HIGH_MASK ; 
 int /*<<< orphan*/  PWM_LOW_MASK ; 
 scalar_t__ REG_MISC_AB ; 
 void* meson_pwm_cnt_to_ns (struct pwm_chip*,struct pwm_device*,scalar_t__) ; 
 struct meson_pwm_channel_data* meson_pwm_per_channel_data ; 
 int readl (scalar_t__) ; 
 struct meson_pwm* to_meson_pwm (struct pwm_chip*) ; 

__attribute__((used)) static void meson_pwm_get_state(struct pwm_chip *chip, struct pwm_device *pwm,
				struct pwm_state *state)
{
	struct meson_pwm *meson = to_meson_pwm(chip);
	struct meson_pwm_channel_data *channel_data;
	struct meson_pwm_channel *channel;
	u32 value, tmp;

	if (!state)
		return;

	channel = &meson->channels[pwm->hwpwm];
	channel_data = &meson_pwm_per_channel_data[pwm->hwpwm];

	value = readl(meson->base + REG_MISC_AB);

	tmp = channel_data->pwm_en_mask | channel_data->clk_en_mask;
	state->enabled = (value & tmp) == tmp;

	tmp = value >> channel_data->clk_div_shift;
	channel->pre_div = FIELD_GET(MISC_CLK_DIV_MASK, tmp);

	value = readl(meson->base + channel_data->reg_offset);

	channel->lo = FIELD_GET(PWM_LOW_MASK, value);
	channel->hi = FIELD_GET(PWM_HIGH_MASK, value);

	if (channel->lo == 0) {
		state->period = meson_pwm_cnt_to_ns(chip, pwm, channel->hi);
		state->duty_cycle = state->period;
	} else if (channel->lo >= channel->hi) {
		state->period = meson_pwm_cnt_to_ns(chip, pwm,
						    channel->lo + channel->hi);
		state->duty_cycle = meson_pwm_cnt_to_ns(chip, pwm,
							channel->hi);
	} else {
		state->period = 0;
		state->duty_cycle = 0;
	}
}