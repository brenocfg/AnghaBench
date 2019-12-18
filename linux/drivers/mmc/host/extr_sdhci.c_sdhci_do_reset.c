#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sdhci_host {int quirks; int flags; int preset_enabled; TYPE_2__* ops; struct mmc_host* mmc; } ;
struct mmc_host {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* enable_dma ) (struct sdhci_host*) ;int /*<<< orphan*/  (* reset ) (struct sdhci_host*,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_cd ) (struct mmc_host*) ;} ;

/* Variables and functions */
 int SDHCI_QUIRK_NO_CARD_NO_RESET ; 
 int SDHCI_RESET_ALL ; 
 int SDHCI_USE_ADMA ; 
 int SDHCI_USE_SDMA ; 
 int /*<<< orphan*/  stub1 (struct mmc_host*) ; 
 int /*<<< orphan*/  stub2 (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  stub3 (struct sdhci_host*) ; 

__attribute__((used)) static void sdhci_do_reset(struct sdhci_host *host, u8 mask)
{
	if (host->quirks & SDHCI_QUIRK_NO_CARD_NO_RESET) {
		struct mmc_host *mmc = host->mmc;

		if (!mmc->ops->get_cd(mmc))
			return;
	}

	host->ops->reset(host, mask);

	if (mask & SDHCI_RESET_ALL) {
		if (host->flags & (SDHCI_USE_SDMA | SDHCI_USE_ADMA)) {
			if (host->ops->enable_dma)
				host->ops->enable_dma(host);
		}

		/* Resetting the controller clears many */
		host->preset_enabled = false;
	}
}