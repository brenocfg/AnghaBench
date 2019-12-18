#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  unsigned long u32 ;
struct rockchip_pwm_chip {TYPE_2__* data; scalar_t__ base; int /*<<< orphan*/  clk; } ;
struct pwm_state {int period; int duty_cycle; scalar_t__ polarity; } ;
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;
struct TYPE_3__ {scalar_t__ ctrl; int /*<<< orphan*/  duty; int /*<<< orphan*/  period; } ;
struct TYPE_4__ {int prescaler; TYPE_1__ regs; scalar_t__ supports_lock; scalar_t__ supports_polarity; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_CLOSEST_ULL (int,int) ; 
 int NSEC_PER_SEC ; 
 unsigned long PWM_DUTY_NEGATIVE ; 
 unsigned long PWM_DUTY_POSITIVE ; 
 unsigned long PWM_INACTIVE_NEGATIVE ; 
 unsigned long PWM_INACTIVE_POSITIVE ; 
 unsigned long PWM_LOCK_EN ; 
 scalar_t__ PWM_POLARITY_INVERSED ; 
 unsigned long PWM_POLARITY_MASK ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 unsigned long readl_relaxed (scalar_t__) ; 
 struct rockchip_pwm_chip* to_rockchip_pwm_chip (struct pwm_chip*) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,scalar_t__) ; 

__attribute__((used)) static void rockchip_pwm_config(struct pwm_chip *chip, struct pwm_device *pwm,
			       const struct pwm_state *state)
{
	struct rockchip_pwm_chip *pc = to_rockchip_pwm_chip(chip);
	unsigned long period, duty;
	u64 clk_rate, div;
	u32 ctrl;

	clk_rate = clk_get_rate(pc->clk);

	/*
	 * Since period and duty cycle registers have a width of 32
	 * bits, every possible input period can be obtained using the
	 * default prescaler value for all practical clock rate values.
	 */
	div = clk_rate * state->period;
	period = DIV_ROUND_CLOSEST_ULL(div,
				       pc->data->prescaler * NSEC_PER_SEC);

	div = clk_rate * state->duty_cycle;
	duty = DIV_ROUND_CLOSEST_ULL(div, pc->data->prescaler * NSEC_PER_SEC);

	/*
	 * Lock the period and duty of previous configuration, then
	 * change the duty and period, that would not be effective.
	 */
	ctrl = readl_relaxed(pc->base + pc->data->regs.ctrl);
	if (pc->data->supports_lock) {
		ctrl |= PWM_LOCK_EN;
		writel_relaxed(ctrl, pc->base + pc->data->regs.ctrl);
	}

	writel(period, pc->base + pc->data->regs.period);
	writel(duty, pc->base + pc->data->regs.duty);

	if (pc->data->supports_polarity) {
		ctrl &= ~PWM_POLARITY_MASK;
		if (state->polarity == PWM_POLARITY_INVERSED)
			ctrl |= PWM_DUTY_NEGATIVE | PWM_INACTIVE_POSITIVE;
		else
			ctrl |= PWM_DUTY_POSITIVE | PWM_INACTIVE_NEGATIVE;
	}

	/*
	 * Unlock and set polarity at the same time,
	 * the configuration of duty, period and polarity
	 * would be effective together at next period.
	 */
	if (pc->data->supports_lock)
		ctrl &= ~PWM_LOCK_EN;

	writel(ctrl, pc->base + pc->data->regs.ctrl);
}