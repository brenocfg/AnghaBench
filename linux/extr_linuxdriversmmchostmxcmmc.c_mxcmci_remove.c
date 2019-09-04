#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mxcmci_host {int /*<<< orphan*/  clk_ipg; int /*<<< orphan*/  clk_per; scalar_t__ dma; TYPE_1__* pdata; } ;
struct mmc_host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* exit ) (int /*<<< orphan*/ *,struct mmc_host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 struct mxcmci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_host (struct mmc_host*) ; 
 struct mmc_host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct mmc_host*) ; 

__attribute__((used)) static int mxcmci_remove(struct platform_device *pdev)
{
	struct mmc_host *mmc = platform_get_drvdata(pdev);
	struct mxcmci_host *host = mmc_priv(mmc);

	mmc_remove_host(mmc);

	if (host->pdata && host->pdata->exit)
		host->pdata->exit(&pdev->dev, mmc);

	if (host->dma)
		dma_release_channel(host->dma);

	clk_disable_unprepare(host->clk_per);
	clk_disable_unprepare(host->clk_ipg);

	mmc_free_host(mmc);

	return 0;
}