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
typedef  int u16 ;
struct rtsx_usb_sdmmc {scalar_t__ host_removal; struct rtsx_ucr* ucr; } ;
struct rtsx_ucr {int /*<<< orphan*/  dev_mutex; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int ENOMEDIUM ; 
 int SD_WP ; 
 struct rtsx_usb_sdmmc* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rtsx_usb_get_card_status (struct rtsx_ucr*,int*) ; 

__attribute__((used)) static int sdmmc_get_ro(struct mmc_host *mmc)
{
	struct rtsx_usb_sdmmc *host = mmc_priv(mmc);
	struct rtsx_ucr *ucr = host->ucr;
	int err;
	u16 val;

	if (host->host_removal)
		return -ENOMEDIUM;

	mutex_lock(&ucr->dev_mutex);

	/* Check SD card detect */
	err = rtsx_usb_get_card_status(ucr, &val);

	mutex_unlock(&ucr->dev_mutex);


	/* Treat failed detection as non-ro */
	if (err)
		return 0;

	if (val & SD_WP)
		return 1;

	return 0;
}