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
struct variant_data {scalar_t__ mmcimask1; } ;
struct mmci_host {int /*<<< orphan*/  clk; scalar_t__ base; struct variant_data* variant; } ;
struct mmc_host {int dummy; } ;
struct amba_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MMCICOMMAND ; 
 scalar_t__ MMCIDATACTRL ; 
 scalar_t__ MMCIMASK0 ; 
 scalar_t__ MMCIMASK1 ; 
 struct mmc_host* amba_get_drvdata (struct amba_device*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 struct mmci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmci_dma_release (struct mmci_host*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int mmci_remove(struct amba_device *dev)
{
	struct mmc_host *mmc = amba_get_drvdata(dev);

	if (mmc) {
		struct mmci_host *host = mmc_priv(mmc);
		struct variant_data *variant = host->variant;

		/*
		 * Undo pm_runtime_put() in probe.  We use the _sync
		 * version here so that we can access the primecell.
		 */
		pm_runtime_get_sync(&dev->dev);

		mmc_remove_host(mmc);

		writel(0, host->base + MMCIMASK0);

		if (variant->mmcimask1)
			writel(0, host->base + MMCIMASK1);

		writel(0, host->base + MMCICOMMAND);
		writel(0, host->base + MMCIDATACTRL);

		mmci_dma_release(host);
		clk_disable_unprepare(host->clk);
		mmc_free_host(mmc);
	}

	return 0;
}