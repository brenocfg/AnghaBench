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
struct gpio_bank {int /*<<< orphan*/  dbck; scalar_t__ dbck_flag; int /*<<< orphan*/  chip; int /*<<< orphan*/  nb; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_pm_unregister_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 struct gpio_bank* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap_gpio_remove(struct platform_device *pdev)
{
	struct gpio_bank *bank = platform_get_drvdata(pdev);

	cpu_pm_unregister_notifier(&bank->nb);
	gpiochip_remove(&bank->chip);
	pm_runtime_disable(&pdev->dev);
	if (bank->dbck_flag)
		clk_unprepare(bank->dbck);

	return 0;
}