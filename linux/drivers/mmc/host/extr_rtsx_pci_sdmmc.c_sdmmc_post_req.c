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
struct rtsx_pcr {int dummy; } ;
struct realtek_pci_sdmmc {struct rtsx_pcr* pcr; } ;
struct mmc_request {struct mmc_data* data; } ;
struct mmc_host {int dummy; } ;
struct mmc_data {int flags; scalar_t__ host_cookie; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;

/* Variables and functions */
 int MMC_DATA_READ ; 
 struct realtek_pci_sdmmc* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  rtsx_pci_dma_unmap_sg (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sdmmc_post_req(struct mmc_host *mmc, struct mmc_request *mrq,
		int err)
{
	struct realtek_pci_sdmmc *host = mmc_priv(mmc);
	struct rtsx_pcr *pcr = host->pcr;
	struct mmc_data *data = mrq->data;
	int read = data->flags & MMC_DATA_READ;

	rtsx_pci_dma_unmap_sg(pcr, data->sg, data->sg_len, read);
	data->host_cookie = 0;
}