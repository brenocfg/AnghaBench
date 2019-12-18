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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ab8500_pwm_chip {int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct ab8500_pwm_chip* platform_get_drvdata (struct platform_device*) ; 
 int pwmchip_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ab8500_pwm_remove(struct platform_device *pdev)
{
	struct ab8500_pwm_chip *ab8500 = platform_get_drvdata(pdev);
	int err;

	err = pwmchip_remove(&ab8500->chip);
	if (err < 0)
		return err;

	dev_dbg(&pdev->dev, "pwm driver removed\n");

	return 0;
}