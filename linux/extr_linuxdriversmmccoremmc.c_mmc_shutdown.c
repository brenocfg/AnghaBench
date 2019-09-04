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
struct mmc_host {int caps2; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int MMC_CAP2_FULL_PWR_CYCLE ; 
 int _mmc_resume (struct mmc_host*) ; 
 int _mmc_suspend (struct mmc_host*,int) ; 
 scalar_t__ mmc_can_poweroff_notify (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmc_shutdown(struct mmc_host *host)
{
	int err = 0;

	/*
	 * In a specific case for poweroff notify, we need to resume the card
	 * before we can shutdown it properly.
	 */
	if (mmc_can_poweroff_notify(host->card) &&
		!(host->caps2 & MMC_CAP2_FULL_PWR_CYCLE))
		err = _mmc_resume(host);

	if (!err)
		err = _mmc_suspend(host, false);

	return err;
}