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
struct mmc_host {int caps; int /*<<< orphan*/  detect; scalar_t__ detect_change; int /*<<< orphan*/  claimed; struct mmc_card* card; } ;
struct mmc_card {int dummy; } ;

/* Variables and functions */
 int MMC_CAP_NEEDS_POLL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int _mmc_detect_card_removed (struct mmc_host*) ; 
 int /*<<< orphan*/  _mmc_detect_change (struct mmc_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_card_is_removable (struct mmc_host*) ; 
 int mmc_card_removed (struct mmc_card*) ; 

int mmc_detect_card_removed(struct mmc_host *host)
{
	struct mmc_card *card = host->card;
	int ret;

	WARN_ON(!host->claimed);

	if (!card)
		return 1;

	if (!mmc_card_is_removable(host))
		return 0;

	ret = mmc_card_removed(card);
	/*
	 * The card will be considered unchanged unless we have been asked to
	 * detect a change or host requires polling to provide card detection.
	 */
	if (!host->detect_change && !(host->caps & MMC_CAP_NEEDS_POLL))
		return ret;

	host->detect_change = 0;
	if (!ret) {
		ret = _mmc_detect_card_removed(host);
		if (ret && (host->caps & MMC_CAP_NEEDS_POLL)) {
			/*
			 * Schedule a detect work as soon as possible to let a
			 * rescan handle the card removal.
			 */
			cancel_delayed_work(&host->detect);
			_mmc_detect_change(host, 0, false);
		}
	}

	return ret;
}