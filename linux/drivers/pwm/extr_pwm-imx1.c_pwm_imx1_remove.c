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
struct pwm_imx1_chip {int /*<<< orphan*/  chip; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct pwm_imx1_chip* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pwm_imx1_clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int pwmchip_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pwm_imx1_remove(struct platform_device *pdev)
{
	struct pwm_imx1_chip *imx = platform_get_drvdata(pdev);

	pwm_imx1_clk_disable_unprepare(&imx->chip);

	return pwmchip_remove(&imx->chip);
}