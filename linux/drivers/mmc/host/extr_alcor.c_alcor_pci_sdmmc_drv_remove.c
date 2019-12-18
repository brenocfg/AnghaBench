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
struct alcor_sdmmc_host {int /*<<< orphan*/  timeout_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  alcor_hw_uninit (struct alcor_sdmmc_host*) ; 
 int /*<<< orphan*/  alcor_request_complete (struct alcor_sdmmc_host*,int /*<<< orphan*/ ) ; 
 scalar_t__ cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct alcor_sdmmc_host* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 struct mmc_host* mmc_from_priv (struct alcor_sdmmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_host (struct mmc_host*) ; 

__attribute__((used)) static int alcor_pci_sdmmc_drv_remove(struct platform_device *pdev)
{
	struct alcor_sdmmc_host *host = dev_get_drvdata(&pdev->dev);
	struct mmc_host *mmc = mmc_from_priv(host);

	if (cancel_delayed_work_sync(&host->timeout_work))
		alcor_request_complete(host, 0);

	alcor_hw_uninit(host);
	mmc_remove_host(mmc);
	mmc_free_host(mmc);

	return 0;
}