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
struct sunxi_mmc_host {int /*<<< orphan*/  sg_dma; int /*<<< orphan*/  sg_cpu; int /*<<< orphan*/  irq; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 struct sunxi_mmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_host (struct mmc_host*) ; 
 struct mmc_host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_force_suspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunxi_mmc_disable (struct sunxi_mmc_host*) ; 

__attribute__((used)) static int sunxi_mmc_remove(struct platform_device *pdev)
{
	struct mmc_host	*mmc = platform_get_drvdata(pdev);
	struct sunxi_mmc_host *host = mmc_priv(mmc);

	mmc_remove_host(mmc);
	pm_runtime_force_suspend(&pdev->dev);
	disable_irq(host->irq);
	sunxi_mmc_disable(host);
	dma_free_coherent(&pdev->dev, PAGE_SIZE, host->sg_cpu, host->sg_dma);
	mmc_free_host(mmc);

	return 0;
}