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
struct zynq_gpio {int /*<<< orphan*/  clk; int /*<<< orphan*/  chip; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 struct zynq_gpio* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zynq_gpio_remove(struct platform_device *pdev)
{
	struct zynq_gpio *gpio = platform_get_drvdata(pdev);

	pm_runtime_get_sync(&pdev->dev);
	gpiochip_remove(&gpio->chip);
	clk_disable_unprepare(gpio->clk);
	device_set_wakeup_capable(&pdev->dev, 0);
	pm_runtime_disable(&pdev->dev);
	return 0;
}