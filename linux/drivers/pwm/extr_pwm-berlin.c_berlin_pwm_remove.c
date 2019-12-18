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
struct platform_device {int dummy; } ;
struct berlin_pwm_chip {int /*<<< orphan*/  clk; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct berlin_pwm_chip* platform_get_drvdata (struct platform_device*) ; 
 int pwmchip_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int berlin_pwm_remove(struct platform_device *pdev)
{
	struct berlin_pwm_chip *pwm = platform_get_drvdata(pdev);
	int ret;

	ret = pwmchip_remove(&pwm->chip);
	clk_disable_unprepare(pwm->clk);

	return ret;
}