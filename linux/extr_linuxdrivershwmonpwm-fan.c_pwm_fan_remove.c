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
struct pwm_fan_ctx {int /*<<< orphan*/  pwm; scalar_t__ pwm_value; int /*<<< orphan*/  cdev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct pwm_fan_ctx* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pwm_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thermal_cooling_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pwm_fan_remove(struct platform_device *pdev)
{
	struct pwm_fan_ctx *ctx = platform_get_drvdata(pdev);

	thermal_cooling_device_unregister(ctx->cdev);
	if (ctx->pwm_value)
		pwm_disable(ctx->pwm);
	return 0;
}