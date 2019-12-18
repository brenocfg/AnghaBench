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
struct rockchip_pwm_chip {int /*<<< orphan*/  pclk; TYPE_1__* data; } ;
struct pwm_state {int enabled; scalar_t__ polarity; } ;
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  supports_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_get_state (struct pwm_device*,struct pwm_state*) ; 
 int /*<<< orphan*/  rockchip_pwm_config (struct pwm_chip*,struct pwm_device*,struct pwm_state const*) ; 
 int rockchip_pwm_enable (struct pwm_chip*,struct pwm_device*,int) ; 
 struct rockchip_pwm_chip* to_rockchip_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static int rockchip_pwm_apply(struct pwm_chip *chip, struct pwm_device *pwm,
			      const struct pwm_state *state)
{
	struct rockchip_pwm_chip *pc = to_rockchip_pwm_chip(chip);
	struct pwm_state curstate;
	bool enabled;
	int ret = 0;

	ret = clk_enable(pc->pclk);
	if (ret)
		return ret;

	pwm_get_state(pwm, &curstate);
	enabled = curstate.enabled;

	if (state->polarity != curstate.polarity && enabled &&
	    !pc->data->supports_lock) {
		ret = rockchip_pwm_enable(chip, pwm, false);
		if (ret)
			goto out;
		enabled = false;
	}

	rockchip_pwm_config(chip, pwm, state);
	if (state->enabled != enabled) {
		ret = rockchip_pwm_enable(chip, pwm, state->enabled);
		if (ret)
			goto out;
	}

out:
	clk_disable(pc->pclk);

	return ret;
}