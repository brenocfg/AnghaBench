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
struct sh_mmcif_host {int dying; int /*<<< orphan*/  mmc; int /*<<< orphan*/  clk; int /*<<< orphan*/  timeout_work; int /*<<< orphan*/  addr; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASK_ALL ; 
 int /*<<< orphan*/  MMCIF_CE_INT_MASK ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_qos_hide_latency_limit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_free_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_remove_host (int /*<<< orphan*/ ) ; 
 struct sh_mmcif_host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sh_mmcif_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_mmcif_remove(struct platform_device *pdev)
{
	struct sh_mmcif_host *host = platform_get_drvdata(pdev);

	host->dying = true;
	clk_prepare_enable(host->clk);
	pm_runtime_get_sync(&pdev->dev);

	dev_pm_qos_hide_latency_limit(&pdev->dev);

	mmc_remove_host(host->mmc);
	sh_mmcif_writel(host->addr, MMCIF_CE_INT_MASK, MASK_ALL);

	/*
	 * FIXME: cancel_delayed_work(_sync)() and free_irq() race with the
	 * mmc_remove_host() call above. But swapping order doesn't help either
	 * (a query on the linux-mmc mailing list didn't bring any replies).
	 */
	cancel_delayed_work_sync(&host->timeout_work);

	clk_disable_unprepare(host->clk);
	mmc_free_host(host->mmc);
	pm_runtime_put_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	return 0;
}