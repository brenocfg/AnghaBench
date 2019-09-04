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
struct platform_device {int dummy; } ;
struct bcm2835_host {int /*<<< orphan*/  mmc; int /*<<< orphan*/  timeout_work; int /*<<< orphan*/  dma_work; int /*<<< orphan*/  irq; scalar_t__ ioaddr; } ;

/* Variables and functions */
 scalar_t__ SDVDD ; 
 int /*<<< orphan*/  SDVDD_POWER_OFF ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct bcm2835_host*) ; 
 int /*<<< orphan*/  mmc_free_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_remove_host (int /*<<< orphan*/ ) ; 
 struct bcm2835_host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int bcm2835_remove(struct platform_device *pdev)
{
	struct bcm2835_host *host = platform_get_drvdata(pdev);

	mmc_remove_host(host->mmc);

	writel(SDVDD_POWER_OFF, host->ioaddr + SDVDD);

	free_irq(host->irq, host);

	cancel_work_sync(&host->dma_work);
	cancel_delayed_work_sync(&host->timeout_work);

	mmc_free_host(host->mmc);
	platform_set_drvdata(pdev, NULL);

	return 0;
}