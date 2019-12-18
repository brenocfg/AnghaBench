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
struct mmc_host {int dummy; } ;
struct goldfish_mmc_host {int /*<<< orphan*/  reg_base; int /*<<< orphan*/  phys_base; int /*<<< orphan*/  virt_base; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_SIZE ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct goldfish_mmc_host*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 struct mmc_host* mmc_from_priv (struct goldfish_mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_host (struct mmc_host*) ; 
 struct goldfish_mmc_host* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int goldfish_mmc_remove(struct platform_device *pdev)
{
	struct goldfish_mmc_host *host = platform_get_drvdata(pdev);
	struct mmc_host *mmc = mmc_from_priv(host);

	BUG_ON(host == NULL);

	mmc_remove_host(mmc);
	free_irq(host->irq, host);
	dma_free_coherent(&pdev->dev, BUFFER_SIZE, host->virt_base, host->phys_base);
	iounmap(host->reg_base);
	mmc_free_host(mmc);
	return 0;
}