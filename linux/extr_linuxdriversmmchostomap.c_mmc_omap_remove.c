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
struct mmc_omap_host {int nr_slots; int /*<<< orphan*/  mmc_omap_wq; scalar_t__ dma_rx; scalar_t__ dma_tx; int /*<<< orphan*/  iclk; int /*<<< orphan*/  fclk; int /*<<< orphan*/  irq; TYPE_1__* pdata; int /*<<< orphan*/ * slots; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cleanup ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mmc_omap_host*) ; 
 int /*<<< orphan*/  mmc_omap_fclk_enable (struct mmc_omap_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_omap_remove_slot (int /*<<< orphan*/ ) ; 
 struct mmc_omap_host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mmc_omap_remove(struct platform_device *pdev)
{
	struct mmc_omap_host *host = platform_get_drvdata(pdev);
	int i;

	BUG_ON(host == NULL);

	for (i = 0; i < host->nr_slots; i++)
		mmc_omap_remove_slot(host->slots[i]);

	if (host->pdata->cleanup)
		host->pdata->cleanup(&pdev->dev);

	mmc_omap_fclk_enable(host, 0);
	free_irq(host->irq, host);
	clk_put(host->fclk);
	clk_disable(host->iclk);
	clk_put(host->iclk);

	if (host->dma_tx)
		dma_release_channel(host->dma_tx);
	if (host->dma_rx)
		dma_release_channel(host->dma_rx);

	destroy_workqueue(host->mmc_omap_wq);

	return 0;
}