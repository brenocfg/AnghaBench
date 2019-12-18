#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {scalar_t__ signal_voltage; } ;
struct mmc_host {int caps; int caps2; struct mmc_card* card; TYPE_4__ ios; scalar_t__ dsr_req; TYPE_1__* ops; int /*<<< orphan*/  claimed; } ;
struct TYPE_7__ {int bus_widths; } ;
struct TYPE_6__ {scalar_t__ dsr_imp; } ;
struct mmc_card {int ocr; TYPE_3__ scr; int /*<<< orphan*/  host; TYPE_2__ csd; int /*<<< orphan*/  rca; int /*<<< orphan*/  raw_cid; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  cid ;
struct TYPE_5__ {int /*<<< orphan*/  (* init_card ) (struct mmc_host*,struct mmc_card*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct mmc_card*) ; 
 int /*<<< orphan*/  MMC_BUS_WIDTH_4 ; 
 int MMC_CAP2_AVOID_3_3V ; 
 int MMC_CAP_4_BIT_DATA ; 
 scalar_t__ MMC_SIGNAL_VOLTAGE_180 ; 
 scalar_t__ MMC_SIGNAL_VOLTAGE_330 ; 
 int /*<<< orphan*/  MMC_TIMING_SD_HS ; 
 int /*<<< orphan*/  MMC_TYPE_SD ; 
 int PTR_ERR (struct mmc_card*) ; 
 int SD_ROCR_S18A ; 
 int SD_SCR_BUS_WIDTH_4 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 struct mmc_card* mmc_alloc_card (struct mmc_host*,int /*<<< orphan*/ *) ; 
 int mmc_app_set_bus_width (struct mmc_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_decode_cid (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_host_is_spi (struct mmc_host*) ; 
 scalar_t__ mmc_host_set_uhs_voltage (struct mmc_host*) ; 
 scalar_t__ mmc_host_uhs (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_power_cycle (struct mmc_host*,int) ; 
 int mmc_read_switch (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_remove_card (struct mmc_card*) ; 
 scalar_t__ mmc_sd_card_using_v18 (struct mmc_card*) ; 
 int mmc_sd_get_cid (struct mmc_host*,int,int*,int*) ; 
 int mmc_sd_get_csd (struct mmc_host*,struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_sd_get_max_clock (struct mmc_card*) ; 
 int mmc_sd_init_uhs_card (struct mmc_card*) ; 
 int mmc_sd_setup_card (struct mmc_host*,struct mmc_card*,int /*<<< orphan*/ ) ; 
 int mmc_sd_switch_hs (struct mmc_card*) ; 
 int mmc_select_card (struct mmc_card*) ; 
 int mmc_send_relative_addr (struct mmc_host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_set_bus_width (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_set_clock (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_set_dsr (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_set_timing (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_type ; 
 int /*<<< orphan*/  stub1 (struct mmc_host*,struct mmc_card*) ; 

__attribute__((used)) static int mmc_sd_init_card(struct mmc_host *host, u32 ocr,
	struct mmc_card *oldcard)
{
	struct mmc_card *card;
	int err;
	u32 cid[4];
	u32 rocr = 0;
	bool v18_fixup_failed = false;

	WARN_ON(!host->claimed);
retry:
	err = mmc_sd_get_cid(host, ocr, cid, &rocr);
	if (err)
		return err;

	if (oldcard) {
		if (memcmp(cid, oldcard->raw_cid, sizeof(cid)) != 0) {
			pr_debug("%s: Perhaps the card was replaced\n",
				mmc_hostname(host));
			return -ENOENT;
		}

		card = oldcard;
	} else {
		/*
		 * Allocate card structure.
		 */
		card = mmc_alloc_card(host, &sd_type);
		if (IS_ERR(card))
			return PTR_ERR(card);

		card->ocr = ocr;
		card->type = MMC_TYPE_SD;
		memcpy(card->raw_cid, cid, sizeof(card->raw_cid));
	}

	/*
	 * Call the optional HC's init_card function to handle quirks.
	 */
	if (host->ops->init_card)
		host->ops->init_card(host, card);

	/*
	 * For native busses:  get card RCA and quit open drain mode.
	 */
	if (!mmc_host_is_spi(host)) {
		err = mmc_send_relative_addr(host, &card->rca);
		if (err)
			goto free_card;
	}

	if (!oldcard) {
		err = mmc_sd_get_csd(host, card);
		if (err)
			goto free_card;

		mmc_decode_cid(card);
	}

	/*
	 * handling only for cards supporting DSR and hosts requesting
	 * DSR configuration
	 */
	if (card->csd.dsr_imp && host->dsr_req)
		mmc_set_dsr(host);

	/*
	 * Select card, as all following commands rely on that.
	 */
	if (!mmc_host_is_spi(host)) {
		err = mmc_select_card(card);
		if (err)
			goto free_card;
	}

	err = mmc_sd_setup_card(host, card, oldcard != NULL);
	if (err)
		goto free_card;

	/*
	 * If the card has not been power cycled, it may still be using 1.8V
	 * signaling. Detect that situation and try to initialize a UHS-I (1.8V)
	 * transfer mode.
	 */
	if (!v18_fixup_failed && !mmc_host_is_spi(host) && mmc_host_uhs(host) &&
	    mmc_sd_card_using_v18(card) &&
	    host->ios.signal_voltage != MMC_SIGNAL_VOLTAGE_180) {
		/*
		 * Re-read switch information in case it has changed since
		 * oldcard was initialized.
		 */
		if (oldcard) {
			err = mmc_read_switch(card);
			if (err)
				goto free_card;
		}
		if (mmc_sd_card_using_v18(card)) {
			if (mmc_host_set_uhs_voltage(host) ||
			    mmc_sd_init_uhs_card(card)) {
				v18_fixup_failed = true;
				mmc_power_cycle(host, ocr);
				if (!oldcard)
					mmc_remove_card(card);
				goto retry;
			}
			goto done;
		}
	}

	/* Initialization sequence for UHS-I cards */
	if (rocr & SD_ROCR_S18A && mmc_host_uhs(host)) {
		err = mmc_sd_init_uhs_card(card);
		if (err)
			goto free_card;
	} else {
		/*
		 * Attempt to change to high-speed (if supported)
		 */
		err = mmc_sd_switch_hs(card);
		if (err > 0)
			mmc_set_timing(card->host, MMC_TIMING_SD_HS);
		else if (err)
			goto free_card;

		/*
		 * Set bus speed.
		 */
		mmc_set_clock(host, mmc_sd_get_max_clock(card));

		/*
		 * Switch to wider bus (if supported).
		 */
		if ((host->caps & MMC_CAP_4_BIT_DATA) &&
			(card->scr.bus_widths & SD_SCR_BUS_WIDTH_4)) {
			err = mmc_app_set_bus_width(card, MMC_BUS_WIDTH_4);
			if (err)
				goto free_card;

			mmc_set_bus_width(host, MMC_BUS_WIDTH_4);
		}
	}

	if (host->caps2 & MMC_CAP2_AVOID_3_3V &&
	    host->ios.signal_voltage == MMC_SIGNAL_VOLTAGE_330) {
		pr_err("%s: Host failed to negotiate down from 3.3V\n",
			mmc_hostname(host));
		err = -EINVAL;
		goto free_card;
	}
done:
	host->card = card;
	return 0;

free_card:
	if (!oldcard)
		mmc_remove_card(card);

	return err;
}