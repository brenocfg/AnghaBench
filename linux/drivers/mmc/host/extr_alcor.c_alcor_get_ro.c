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
 int /*<<< orphan*/  AU6601_INTERFACE_MODE_CTRL ; 
 int AU6601_SD_CARD_WP ; 
 int alcor_read8 (struct alcor_pci_priv*,int /*<<< orphan*/ ) ; 
 struct alcor_sdmmc_host* mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static int alcor_get_ro(struct mmc_host *mmc)
{
	struct alcor_sdmmc_host *host = mmc_priv(mmc);
	struct alcor_pci_priv *priv = host->alcor_pci;
	u8 status;

	/* get write protect pin status */
	status = alcor_read8(priv, AU6601_INTERFACE_MODE_CTRL);

	return !!(status & AU6601_SD_CARD_WP);
}