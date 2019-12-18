#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pwm_state {int enabled; int /*<<< orphan*/  duty_cycle; } ;
struct pwm_fan_ctx {unsigned long pwm_value; int /*<<< orphan*/  lock; TYPE_2__* pwm; } ;
struct TYPE_4__ {unsigned long period; } ;
struct TYPE_5__ {TYPE_1__ args; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_PWM ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pwm_apply_state (TYPE_2__*,struct pwm_state*) ; 
 int /*<<< orphan*/  pwm_init_state (TYPE_2__*,struct pwm_state*) ; 

__attribute__((used)) static int  __set_pwm(struct pwm_fan_ctx *ctx, unsigned long pwm)
{
	unsigned long period;
	int ret = 0;
	struct pwm_state state = { };

	mutex_lock(&ctx->lock);
	if (ctx->pwm_value == pwm)
		goto exit_set_pwm_err;

	pwm_init_state(ctx->pwm, &state);
	period = ctx->pwm->args.period;
	state.duty_cycle = DIV_ROUND_UP(pwm * (period - 1), MAX_PWM);
	state.enabled = pwm ? true : false;

	ret = pwm_apply_state(ctx->pwm, &state);
	if (!ret)
		ctx->pwm_value = pwm;
exit_set_pwm_err:
	mutex_unlock(&ctx->lock);
	return ret;
}