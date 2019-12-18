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
typedef  int u8 ;
struct mmc_host {int dummy; } ;
struct alcor_sdmmc_host {struct alcor_pci_priv* alcor_pci; } ;
struct alcor_pci_priv {int dummy; } ;

/* Variables and functions */
 int AU6601_BUS_STAT_DAT_MASK ; 
 int /*<<< orphan*/  AU6601_DATA_PIN_STATE ; 
 int alcor_read8 (struct alcor_pci_priv*,int /*<<< orphan*/ ) ; 
 struct alcor_sdmmc_host* mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static int alcor_card_busy(struct mmc_host *mmc)
{
	struct alcor_sdmmc_host *host = mmc_priv(mmc);
	struct alcor_pci_priv *priv = host->alcor_pci;
	u8 status;

	/* Check whether dat[0:3] low */
	status = alcor_read8(priv, AU6601_DATA_PIN_STATE);

	return !(status & AU6601_BUS_STAT_DAT_MASK);
}