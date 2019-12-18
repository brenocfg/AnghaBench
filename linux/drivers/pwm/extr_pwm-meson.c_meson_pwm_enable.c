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
struct pwm_device {size_t hwpwm; } ;
struct meson_pwm_channel_data {int clk_div_shift; int clk_en_mask; int pwm_en_mask; scalar_t__ reg_offset; } ;
struct meson_pwm_channel {int pre_div; int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct meson_pwm {int /*<<< orphan*/  lock; scalar_t__ base; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MISC_CLK_DIV_MASK ; 
 int /*<<< orphan*/  PWM_HIGH_MASK ; 
 int /*<<< orphan*/  PWM_LOW_MASK ; 
 scalar_t__ REG_MISC_AB ; 
 struct meson_pwm_channel_data* meson_pwm_per_channel_data ; 
 struct meson_pwm_channel* pwm_get_chip_data (struct pwm_device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void meson_pwm_enable(struct meson_pwm *meson, struct pwm_device *pwm)
{
	struct meson_pwm_channel *channel = pwm_get_chip_data(pwm);
	struct meson_pwm_channel_data *channel_data;
	unsigned long flags;
	u32 value;

	channel_data = &meson_pwm_per_channel_data[pwm->hwpwm];

	spin_lock_irqsave(&meson->lock, flags);

	value = readl(meson->base + REG_MISC_AB);
	value &= ~(MISC_CLK_DIV_MASK << channel_data->clk_div_shift);
	value |= channel->pre_div << channel_data->clk_div_shift;
	value |= channel_data->clk_en_mask;
	writel(value, meson->base + REG_MISC_AB);

	value = FIELD_PREP(PWM_HIGH_MASK, channel->hi) |
		FIELD_PREP(PWM_LOW_MASK, channel->lo);
	writel(value, meson->base + channel_data->reg_offset);

	value = readl(meson->base + REG_MISC_AB);
	value |= channel_data->pwm_en_mask;
	writel(value, meson->base + REG_MISC_AB);

	spin_unlock_irqrestore(&meson->lock, flags);
}