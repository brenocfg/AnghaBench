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
struct gpmc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpmc_free_irq (struct gpmc_device*) ; 
 int /*<<< orphan*/  gpmc_mem_exit () ; 
 struct gpmc_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gpmc_remove(struct platform_device *pdev)
{
	struct gpmc_device *gpmc = platform_get_drvdata(pdev);

	gpmc_free_irq(gpmc);
	gpmc_mem_exit();
	pm_runtime_put_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	return 0;
}