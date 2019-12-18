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
typedef  int u64 ;
struct timer_list {int dummy; } ;
struct pwm_fan_ctx {int pulses_per_revolution; int rpm; int /*<<< orphan*/  rpm_timer; int /*<<< orphan*/  sample_start; int /*<<< orphan*/  pulses; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 struct pwm_fan_ctx* ctx ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 struct pwm_fan_ctx* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  ktime_get () ; 
 int ktime_ms_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  rpm_timer ; 

__attribute__((used)) static void sample_timer(struct timer_list *t)
{
	struct pwm_fan_ctx *ctx = from_timer(ctx, t, rpm_timer);
	int pulses;
	u64 tmp;

	pulses = atomic_read(&ctx->pulses);
	atomic_sub(pulses, &ctx->pulses);
	tmp = (u64)pulses * ktime_ms_delta(ktime_get(), ctx->sample_start) * 60;
	do_div(tmp, ctx->pulses_per_revolution * 1000);
	ctx->rpm = tmp;

	ctx->sample_start = ktime_get();
	mod_timer(&ctx->rpm_timer, jiffies + HZ);
}