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
struct mxcmci_host {int dummy; } ;
struct mmc_host {int /*<<< orphan*/  caps; } ;
struct mmc_card {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_CAP_4_BIT_DATA ; 
 scalar_t__ MMC_TYPE_SDIO ; 
 scalar_t__ is_imx31_mmc (struct mxcmci_host*) ; 
 struct mxcmci_host* mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static void mxcmci_init_card(struct mmc_host *host, struct mmc_card *card)
{
	struct mxcmci_host *mxcmci = mmc_priv(host);

	/*
	 * MX3 SoCs have a silicon bug which corrupts CRC calculation of
	 * multi-block transfers when connected SDIO peripheral doesn't
	 * drive the BUSY line as required by the specs.
	 * One way to prevent this is to only allow 1-bit transfers.
	 */

	if (is_imx31_mmc(mxcmci) && card->type == MMC_TYPE_SDIO)
		host->caps &= ~MMC_CAP_4_BIT_DATA;
	else
		host->caps |= MMC_CAP_4_BIT_DATA;
}