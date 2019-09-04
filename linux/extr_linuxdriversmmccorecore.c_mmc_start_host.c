#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  power_mode; } ;
struct mmc_host {int caps2; int /*<<< orphan*/  ocr_avail; TYPE_1__ ios; scalar_t__ rescan_disable; int /*<<< orphan*/  f_min; int /*<<< orphan*/  f_init; } ;

/* Variables and functions */
 int MMC_CAP2_NO_PRESCAN_POWERUP ; 
 int /*<<< orphan*/  MMC_POWER_UNDEFINED ; 
 int /*<<< orphan*/  _mmc_detect_change (struct mmc_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * freqs ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_claim_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_gpiod_request_cd_irq (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_power_up (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_release_host (struct mmc_host*) ; 

void mmc_start_host(struct mmc_host *host)
{
	host->f_init = max(freqs[0], host->f_min);
	host->rescan_disable = 0;
	host->ios.power_mode = MMC_POWER_UNDEFINED;

	if (!(host->caps2 & MMC_CAP2_NO_PRESCAN_POWERUP)) {
		mmc_claim_host(host);
		mmc_power_up(host, host->ocr_avail);
		mmc_release_host(host);
	}

	mmc_gpiod_request_cd_irq(host);
	_mmc_detect_change(host, 0, false);
}