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
struct rpi_poe_fan_ctx {scalar_t__ def_pwm_value; scalar_t__ pwm_value; int /*<<< orphan*/  fw; int /*<<< orphan*/  cdev; int /*<<< orphan*/  nb; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  POE_CUR_PWM ; 
 struct rpi_poe_fan_ctx* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  thermal_cooling_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int rpi_poe_fan_remove(struct platform_device *pdev)
{
	struct rpi_poe_fan_ctx *ctx = platform_get_drvdata(pdev);
	u32 value = ctx->def_pwm_value;

	unregister_reboot_notifier(&ctx->nb);
	thermal_cooling_device_unregister(ctx->cdev);
	if (ctx->pwm_value != value) {
		write_reg(ctx->fw, POE_CUR_PWM, &value);
	}
	return 0;
}