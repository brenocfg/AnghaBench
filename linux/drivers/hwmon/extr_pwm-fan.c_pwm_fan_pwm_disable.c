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
struct pwm_fan_ctx {int /*<<< orphan*/  rpm_timer; int /*<<< orphan*/  pwm; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwm_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pwm_fan_pwm_disable(void *__ctx)
{
	struct pwm_fan_ctx *ctx = __ctx;
	pwm_disable(ctx->pwm);
	del_timer_sync(&ctx->rpm_timer);
}