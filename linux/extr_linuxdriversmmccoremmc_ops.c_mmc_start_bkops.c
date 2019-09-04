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
struct TYPE_2__ {scalar_t__ raw_bkops_status; int /*<<< orphan*/  man_bkops_en; } ;
struct mmc_card {int /*<<< orphan*/  host; TYPE_1__ ext_csd; } ;

/* Variables and functions */
 scalar_t__ EXT_CSD_BKOPS_LEVEL_2 ; 
 int /*<<< orphan*/  EXT_CSD_BKOPS_START ; 
 int /*<<< orphan*/  EXT_CSD_CMD_SET_NORMAL ; 
 int MMC_OPS_TIMEOUT_MS ; 
 int __mmc_switch (struct mmc_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ mmc_card_doing_bkops (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_card_set_doing_bkops (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int mmc_read_bkops_status (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_retune_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_retune_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 

void mmc_start_bkops(struct mmc_card *card, bool from_exception)
{
	int err;
	int timeout;
	bool use_busy_signal;

	if (!card->ext_csd.man_bkops_en || mmc_card_doing_bkops(card))
		return;

	err = mmc_read_bkops_status(card);
	if (err) {
		pr_err("%s: Failed to read bkops status: %d\n",
		       mmc_hostname(card->host), err);
		return;
	}

	if (!card->ext_csd.raw_bkops_status)
		return;

	if (card->ext_csd.raw_bkops_status < EXT_CSD_BKOPS_LEVEL_2 &&
	    from_exception)
		return;

	if (card->ext_csd.raw_bkops_status >= EXT_CSD_BKOPS_LEVEL_2) {
		timeout = MMC_OPS_TIMEOUT_MS;
		use_busy_signal = true;
	} else {
		timeout = 0;
		use_busy_signal = false;
	}

	mmc_retune_hold(card->host);

	err = __mmc_switch(card, EXT_CSD_CMD_SET_NORMAL,
			EXT_CSD_BKOPS_START, 1, timeout, 0,
			use_busy_signal, true, false);
	if (err) {
		pr_warn("%s: Error %d starting bkops\n",
			mmc_hostname(card->host), err);
		mmc_retune_release(card->host);
		return;
	}

	/*
	 * For urgent bkops status (LEVEL_2 and more)
	 * bkops executed synchronously, otherwise
	 * the operation is in progress
	 */
	if (!use_busy_signal)
		mmc_card_set_doing_bkops(card);
	else
		mmc_retune_release(card->host);
}