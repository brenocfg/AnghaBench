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
struct realtek_pci_sdmmc {int /*<<< orphan*/  cookie_sg_count; } ;
struct mmc_request {struct mmc_data* data; } ;
struct mmc_host {int dummy; } ;
struct mmc_data {scalar_t__ host_cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 struct realtek_pci_sdmmc* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  sd_pre_dma_transfer (struct realtek_pci_sdmmc*,struct mmc_data*,int) ; 
 int /*<<< orphan*/  sdmmc_dev (struct realtek_pci_sdmmc*) ; 

__attribute__((used)) static void sdmmc_pre_req(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct realtek_pci_sdmmc *host = mmc_priv(mmc);
	struct mmc_data *data = mrq->data;

	if (data->host_cookie) {
		dev_err(sdmmc_dev(host),
			"error: reset data->host_cookie = %d\n",
			data->host_cookie);
		data->host_cookie = 0;
	}

	sd_pre_dma_transfer(host, data, true);
	dev_dbg(sdmmc_dev(host), "pre dma sg: %d\n", host->cookie_sg_count);
}