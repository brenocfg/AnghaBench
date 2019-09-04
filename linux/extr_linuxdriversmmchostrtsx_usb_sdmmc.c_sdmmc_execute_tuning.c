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
typedef  int /*<<< orphan*/  u32 ;
struct rtsx_usb_sdmmc {int /*<<< orphan*/  ddr_mode; scalar_t__ host_removal; struct rtsx_ucr* ucr; } ;
struct rtsx_ucr {int /*<<< orphan*/  dev_mutex; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int ENOMEDIUM ; 
 int /*<<< orphan*/  MMC_SEND_TUNING_BLOCK ; 
 struct rtsx_usb_sdmmc* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sd_tuning_rx (struct rtsx_usb_sdmmc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdmmc_execute_tuning(struct mmc_host *mmc, u32 opcode)
{
	struct rtsx_usb_sdmmc *host = mmc_priv(mmc);
	struct rtsx_ucr *ucr = host->ucr;
	int err = 0;

	if (host->host_removal)
		return -ENOMEDIUM;

	mutex_lock(&ucr->dev_mutex);

	if (!host->ddr_mode)
		err = sd_tuning_rx(host, MMC_SEND_TUNING_BLOCK);

	mutex_unlock(&ucr->dev_mutex);

	return err;
}