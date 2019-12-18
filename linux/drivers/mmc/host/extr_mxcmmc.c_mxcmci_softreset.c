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
struct mxcmci_host {int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_REG_RES_TO ; 
 int /*<<< orphan*/  MMC_REG_STR_STP_CLK ; 
 int STR_STP_CLK_RESET ; 
 int STR_STP_CLK_START_CLK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxcmci_writew (struct mxcmci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mxcmci_softreset(struct mxcmci_host *host)
{
	int i;

	dev_dbg(mmc_dev(host->mmc), "mxcmci_softreset\n");

	/* reset sequence */
	mxcmci_writew(host, STR_STP_CLK_RESET, MMC_REG_STR_STP_CLK);
	mxcmci_writew(host, STR_STP_CLK_RESET | STR_STP_CLK_START_CLK,
			MMC_REG_STR_STP_CLK);

	for (i = 0; i < 8; i++)
		mxcmci_writew(host, STR_STP_CLK_START_CLK, MMC_REG_STR_STP_CLK);

	mxcmci_writew(host, 0xff, MMC_REG_RES_TO);
}