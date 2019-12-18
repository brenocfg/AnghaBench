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
typedef  int /*<<< orphan*/  u32 ;
struct pwm_device {size_t hwpwm; } ;
struct meson_pwm {int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct TYPE_2__ {int /*<<< orphan*/  pwm_en_mask; } ;

/* Variables and functions */
 scalar_t__ REG_MISC_AB ; 
 TYPE_1__* meson_pwm_per_channel_data ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_pwm_disable(struct meson_pwm *meson, struct pwm_device *pwm)
{
	unsigned long flags;
	u32 value;

	spin_lock_irqsave(&meson->lock, flags);

	value = readl(meson->base + REG_MISC_AB);
	value &= ~meson_pwm_per_channel_data[pwm->hwpwm].pwm_en_mask;
	writel(value, meson->base + REG_MISC_AB);

	spin_unlock_irqrestore(&meson->lock, flags);
}