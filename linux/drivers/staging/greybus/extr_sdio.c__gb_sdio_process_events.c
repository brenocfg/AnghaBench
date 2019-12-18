#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct gb_sdio_host {int card_present; int read_only; TYPE_1__* mmc; } ;
struct TYPE_3__ {int caps; } ;

/* Variables and functions */
 int GB_SDIO_CARD_INSERTED ; 
 int GB_SDIO_CARD_REMOVED ; 
 int GB_SDIO_WP ; 
 int MMC_CAP_NONREMOVABLE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  mmc_detect_change (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (TYPE_1__*) ; 

__attribute__((used)) static int _gb_sdio_process_events(struct gb_sdio_host *host, u8 event)
{
	u8 state_changed = 0;

	if (event & GB_SDIO_CARD_INSERTED) {
		if (host->mmc->caps & MMC_CAP_NONREMOVABLE)
			return 0;
		if (host->card_present)
			return 0;
		host->card_present = true;
		state_changed = 1;
	}

	if (event & GB_SDIO_CARD_REMOVED) {
		if (host->mmc->caps & MMC_CAP_NONREMOVABLE)
			return 0;
		if (!(host->card_present))
			return 0;
		host->card_present = false;
		state_changed = 1;
	}

	if (event & GB_SDIO_WP)
		host->read_only = true;

	if (state_changed) {
		dev_info(mmc_dev(host->mmc), "card %s now event\n",
			 (host->card_present ?  "inserted" : "removed"));
		mmc_detect_change(host->mmc, 0);
	}

	return 0;
}