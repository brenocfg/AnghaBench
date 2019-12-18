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
struct realtek_pci_sdmmc {int /*<<< orphan*/  work; int /*<<< orphan*/  using_cookie; int /*<<< orphan*/  host_mutex; struct mmc_request* mrq; } ;
struct mmc_request {int /*<<< orphan*/  cmd; struct mmc_data* data; } ;
struct mmc_host {int dummy; } ;
struct mmc_data {int dummy; } ;

/* Variables and functions */
 struct realtek_pci_sdmmc* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_pre_dma_transfer (struct realtek_pci_sdmmc*,struct mmc_data*,int) ; 
 scalar_t__ sd_rw_cmd (int /*<<< orphan*/ ) ; 
 scalar_t__ sdio_extblock_cmd (int /*<<< orphan*/ ,struct mmc_data*) ; 

__attribute__((used)) static void sdmmc_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct realtek_pci_sdmmc *host = mmc_priv(mmc);
	struct mmc_data *data = mrq->data;

	mutex_lock(&host->host_mutex);
	host->mrq = mrq;
	mutex_unlock(&host->host_mutex);

	if (sd_rw_cmd(mrq->cmd) || sdio_extblock_cmd(mrq->cmd, data))
		host->using_cookie = sd_pre_dma_transfer(host, data, false);

	schedule_work(&host->work);
}