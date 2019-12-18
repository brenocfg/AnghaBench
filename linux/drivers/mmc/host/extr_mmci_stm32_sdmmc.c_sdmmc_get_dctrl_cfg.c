#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mmci_host {TYPE_1__* mrq; TYPE_3__* data; TYPE_2__* mmc; } ;
struct TYPE_6__ {int blocks; scalar_t__ stop; } ;
struct TYPE_5__ {scalar_t__ card; } ;
struct TYPE_4__ {int /*<<< orphan*/  sbc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCI_DPSM_STM32_MODE_BLOCK ; 
 int /*<<< orphan*/  MCI_DPSM_STM32_MODE_BLOCK_STOP ; 
 int /*<<< orphan*/  MCI_DPSM_STM32_MODE_SDIO ; 
 scalar_t__ mmc_card_sdio (scalar_t__) ; 
 int /*<<< orphan*/  mmci_dctrl_blksz (struct mmci_host*) ; 

__attribute__((used)) static u32 sdmmc_get_dctrl_cfg(struct mmci_host *host)
{
	u32 datactrl;

	datactrl = mmci_dctrl_blksz(host);

	if (host->mmc->card && mmc_card_sdio(host->mmc->card) &&
	    host->data->blocks == 1)
		datactrl |= MCI_DPSM_STM32_MODE_SDIO;
	else if (host->data->stop && !host->mrq->sbc)
		datactrl |= MCI_DPSM_STM32_MODE_BLOCK_STOP;
	else
		datactrl |= MCI_DPSM_STM32_MODE_BLOCK;

	return datactrl;
}