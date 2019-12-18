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
struct omap_hsmmc_host {int /*<<< orphan*/  mmc; scalar_t__ dbclk; int /*<<< orphan*/  dev; int /*<<< orphan*/  rx_chan; int /*<<< orphan*/  tx_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  dev_pm_clear_wake_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_free_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_remove_host (int /*<<< orphan*/ ) ; 
 struct omap_hsmmc_host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_hsmmc_remove(struct platform_device *pdev)
{
	struct omap_hsmmc_host *host = platform_get_drvdata(pdev);

	pm_runtime_get_sync(host->dev);
	mmc_remove_host(host->mmc);

	dma_release_channel(host->tx_chan);
	dma_release_channel(host->rx_chan);

	dev_pm_clear_wake_irq(host->dev);
	pm_runtime_dont_use_autosuspend(host->dev);
	pm_runtime_put_sync(host->dev);
	pm_runtime_disable(host->dev);
	device_init_wakeup(&pdev->dev, false);
	if (host->dbclk)
		clk_disable_unprepare(host->dbclk);

	mmc_free_host(host->mmc);

	return 0;
}