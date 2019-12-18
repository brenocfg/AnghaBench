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
struct mxs_ssp {int /*<<< orphan*/  clk; scalar_t__ dmach; } ;
struct mxs_mmc_host {struct mxs_ssp ssp; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 struct mxs_mmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_host (struct mmc_host*) ; 
 struct mmc_host* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mxs_mmc_remove(struct platform_device *pdev)
{
	struct mmc_host *mmc = platform_get_drvdata(pdev);
	struct mxs_mmc_host *host = mmc_priv(mmc);
	struct mxs_ssp *ssp = &host->ssp;

	mmc_remove_host(mmc);

	if (ssp->dmach)
		dma_release_channel(ssp->dmach);

	clk_disable_unprepare(ssp->clk);

	mmc_free_host(mmc);

	return 0;
}