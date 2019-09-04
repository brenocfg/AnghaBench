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
typedef  scalar_t__ u32 ;
struct rpi_poe_fan_ctx {scalar_t__ def_pwm_value; int /*<<< orphan*/  lock; int /*<<< orphan*/  fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  POE_CUR_PWM ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int  __set_def_pwm(struct rpi_poe_fan_ctx *ctx, u32 def_pwm)
{
	int ret = 0;
	mutex_lock(&ctx->lock);
	if (ctx->def_pwm_value == def_pwm)
		goto exit_set_def_pwm_err;

	ret = write_reg(ctx->fw, POE_CUR_PWM, &def_pwm);
	if (!ret)
		ctx->def_pwm_value = def_pwm;
exit_set_def_pwm_err:
	mutex_unlock(&ctx->lock);
	return ret;
}