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
struct sdhci_sprd_host {int /*<<< orphan*/  clk_2x_enable; int /*<<< orphan*/  clk_enable; int /*<<< orphan*/  clk_sdio; } ;
struct sdhci_host {struct mmc_host* mmc; } ;
struct platform_device {int dummy; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 struct sdhci_sprd_host* TO_SPRD_HOST (struct sdhci_host*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_host (struct mmc_host*) ; 
 struct sdhci_host* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int sdhci_sprd_remove(struct platform_device *pdev)
{
	struct sdhci_host *host = platform_get_drvdata(pdev);
	struct sdhci_sprd_host *sprd_host = TO_SPRD_HOST(host);
	struct mmc_host *mmc = host->mmc;

	mmc_remove_host(mmc);
	clk_disable_unprepare(sprd_host->clk_sdio);
	clk_disable_unprepare(sprd_host->clk_enable);
	clk_disable_unprepare(sprd_host->clk_2x_enable);

	mmc_free_host(mmc);

	return 0;
}