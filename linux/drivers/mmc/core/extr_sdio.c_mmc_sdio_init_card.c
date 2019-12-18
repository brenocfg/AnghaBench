#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_12__ {scalar_t__ signal_voltage; } ;
struct mmc_host {int caps2; struct mmc_card* card; TYPE_6__ ios; TYPE_1__* ops; int /*<<< orphan*/  claimed; } ;
struct TYPE_11__ {scalar_t__ sd3_bus_mode; } ;
struct TYPE_10__ {int /*<<< orphan*/ * type; } ;
struct TYPE_9__ {scalar_t__ vendor; scalar_t__ device; int /*<<< orphan*/  max_dtr; } ;
struct TYPE_8__ {scalar_t__ high_speed; } ;
struct mmc_card {scalar_t__ type; int quirks; int ocr; int /*<<< orphan*/  host; TYPE_5__ sw_caps; TYPE_4__ dev; TYPE_3__ cis; TYPE_2__ cccr; int /*<<< orphan*/  rca; int /*<<< orphan*/  raw_cid; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* init_card ) (struct mmc_host*,struct mmc_card*) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct mmc_card*) ; 
 int MMC_CAP2_AVOID_3_3V ; 
 int MMC_QUIRK_NONSTD_SDIO ; 
 scalar_t__ MMC_SIGNAL_VOLTAGE_330 ; 
 int /*<<< orphan*/  MMC_TIMING_SD_HS ; 
 scalar_t__ MMC_TYPE_SDIO ; 
 scalar_t__ MMC_TYPE_SD_COMBO ; 
 int PTR_ERR (struct mmc_card*) ; 
 int R4_18V_PRESENT ; 
 int R4_MEMORY_PRESENT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mmc_card* mmc_alloc_card (struct mmc_host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_decode_cid (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_fixup_device (struct mmc_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_go_idle (struct mmc_host*) ; 
 scalar_t__ mmc_host_is_spi (struct mmc_host*) ; 
 scalar_t__ mmc_host_uhs (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_card (struct mmc_card*) ; 
 scalar_t__ mmc_sd_get_cid (struct mmc_host*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mmc_sd_get_csd (struct mmc_host*,struct mmc_card*) ; 
 int mmc_sd_setup_card (struct mmc_host*,struct mmc_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_sdio_get_max_clock (struct mmc_card*) ; 
 int mmc_sdio_init_uhs_card (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_sdio_resend_if_cond (struct mmc_host*,struct mmc_card*) ; 
 int mmc_select_card (struct mmc_card*) ; 
 int mmc_send_io_op_cond (struct mmc_host*,int,int*) ; 
 int mmc_send_relative_addr (struct mmc_host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_set_clock (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_set_timing (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mmc_set_uhs_voltage (struct mmc_host*,int) ; 
 int mmc_spi_set_crc (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_type ; 
 int sdio_disable_cd (struct mmc_card*) ; 
 int sdio_enable_4bit_bus (struct mmc_card*) ; 
 int sdio_enable_hs (struct mmc_card*) ; 
 int /*<<< orphan*/  sdio_fixup_methods ; 
 int sdio_read_cccr (struct mmc_card*,int) ; 
 int sdio_read_common_cis (struct mmc_card*) ; 
 int /*<<< orphan*/  stub1 (struct mmc_host*,struct mmc_card*) ; 
 int /*<<< orphan*/  use_spi_crc ; 

__attribute__((used)) static int mmc_sdio_init_card(struct mmc_host *host, u32 ocr,
			      struct mmc_card *oldcard)
{
	struct mmc_card *card;
	int err;
	int retries = 10;
	u32 rocr = 0;
	u32 ocr_card = ocr;

	WARN_ON(!host->claimed);

	/* to query card if 1.8V signalling is supported */
	if (mmc_host_uhs(host))
		ocr |= R4_18V_PRESENT;

try_again:
	if (!retries) {
		pr_warn("%s: Skipping voltage switch\n", mmc_hostname(host));
		ocr &= ~R4_18V_PRESENT;
	}

	/*
	 * Inform the card of the voltage
	 */
	err = mmc_send_io_op_cond(host, ocr, &rocr);
	if (err)
		goto err;

	/*
	 * For SPI, enable CRC as appropriate.
	 */
	if (mmc_host_is_spi(host)) {
		err = mmc_spi_set_crc(host, use_spi_crc);
		if (err)
			goto err;
	}

	/*
	 * Allocate card structure.
	 */
	card = mmc_alloc_card(host, NULL);
	if (IS_ERR(card)) {
		err = PTR_ERR(card);
		goto err;
	}

	if ((rocr & R4_MEMORY_PRESENT) &&
	    mmc_sd_get_cid(host, ocr & rocr, card->raw_cid, NULL) == 0) {
		card->type = MMC_TYPE_SD_COMBO;

		if (oldcard && (oldcard->type != MMC_TYPE_SD_COMBO ||
		    memcmp(card->raw_cid, oldcard->raw_cid, sizeof(card->raw_cid)) != 0)) {
			mmc_remove_card(card);
			pr_debug("%s: Perhaps the card was replaced\n",
				mmc_hostname(host));
			return -ENOENT;
		}
	} else {
		card->type = MMC_TYPE_SDIO;

		if (oldcard && oldcard->type != MMC_TYPE_SDIO) {
			mmc_remove_card(card);
			pr_debug("%s: Perhaps the card was replaced\n",
				mmc_hostname(host));
			return -ENOENT;
		}
	}

	/*
	 * Call the optional HC's init_card function to handle quirks.
	 */
	if (host->ops->init_card)
		host->ops->init_card(host, card);

	/*
	 * If the host and card support UHS-I mode request the card
	 * to switch to 1.8V signaling level.  No 1.8v signalling if
	 * UHS mode is not enabled to maintain compatibility and some
	 * systems that claim 1.8v signalling in fact do not support
	 * it. Per SDIO spec v3, section 3.1.2, if the voltage is already
	 * 1.8v, the card sets S18A to 0 in the R4 response. So it will
	 * fails to check rocr & R4_18V_PRESENT,  but we still need to
	 * try to init uhs card. sdio_read_cccr will take over this task
	 * to make sure which speed mode should work.
	 */
	if (rocr & ocr & R4_18V_PRESENT) {
		err = mmc_set_uhs_voltage(host, ocr_card);
		if (err == -EAGAIN) {
			mmc_sdio_resend_if_cond(host, card);
			retries--;
			goto try_again;
		} else if (err) {
			ocr &= ~R4_18V_PRESENT;
		}
	}

	/*
	 * For native busses:  set card RCA and quit open drain mode.
	 */
	if (!mmc_host_is_spi(host)) {
		err = mmc_send_relative_addr(host, &card->rca);
		if (err)
			goto remove;

		/*
		 * Update oldcard with the new RCA received from the SDIO
		 * device -- we're doing this so that it's updated in the
		 * "card" struct when oldcard overwrites that later.
		 */
		if (oldcard)
			oldcard->rca = card->rca;
	}

	/*
	 * Read CSD, before selecting the card
	 */
	if (!oldcard && card->type == MMC_TYPE_SD_COMBO) {
		err = mmc_sd_get_csd(host, card);
		if (err)
			return err;

		mmc_decode_cid(card);
	}

	/*
	 * Select card, as all following commands rely on that.
	 */
	if (!mmc_host_is_spi(host)) {
		err = mmc_select_card(card);
		if (err)
			goto remove;
	}

	if (card->quirks & MMC_QUIRK_NONSTD_SDIO) {
		/*
		 * This is non-standard SDIO device, meaning it doesn't
		 * have any CIA (Common I/O area) registers present.
		 * It's host's responsibility to fill cccr and cis
		 * structures in init_card().
		 */
		mmc_set_clock(host, card->cis.max_dtr);

		if (card->cccr.high_speed) {
			mmc_set_timing(card->host, MMC_TIMING_SD_HS);
		}

		goto finish;
	}

	/*
	 * Read the common registers. Note that we should try to
	 * validate whether UHS would work or not.
	 */
	err = sdio_read_cccr(card, ocr);
	if (err) {
		mmc_sdio_resend_if_cond(host, card);
		if (ocr & R4_18V_PRESENT) {
			/* Retry init sequence, but without R4_18V_PRESENT. */
			retries = 0;
			goto try_again;
		} else {
			goto remove;
		}
	}

	/*
	 * Read the common CIS tuples.
	 */
	err = sdio_read_common_cis(card);
	if (err)
		goto remove;

	if (oldcard) {
		int same = (card->cis.vendor == oldcard->cis.vendor &&
			    card->cis.device == oldcard->cis.device);
		mmc_remove_card(card);
		if (!same) {
			pr_debug("%s: Perhaps the card was replaced\n",
				mmc_hostname(host));
			return -ENOENT;
		}

		card = oldcard;
	}
	card->ocr = ocr_card;
	mmc_fixup_device(card, sdio_fixup_methods);

	if (card->type == MMC_TYPE_SD_COMBO) {
		err = mmc_sd_setup_card(host, card, oldcard != NULL);
		/* handle as SDIO-only card if memory init failed */
		if (err) {
			mmc_go_idle(host);
			if (mmc_host_is_spi(host))
				/* should not fail, as it worked previously */
				mmc_spi_set_crc(host, use_spi_crc);
			card->type = MMC_TYPE_SDIO;
		} else
			card->dev.type = &sd_type;
	}

	/*
	 * If needed, disconnect card detection pull-up resistor.
	 */
	err = sdio_disable_cd(card);
	if (err)
		goto remove;

	/* Initialization sequence for UHS-I cards */
	/* Only if card supports 1.8v and UHS signaling */
	if ((ocr & R4_18V_PRESENT) && card->sw_caps.sd3_bus_mode) {
		err = mmc_sdio_init_uhs_card(card);
		if (err)
			goto remove;
	} else {
		/*
		 * Switch to high-speed (if supported).
		 */
		err = sdio_enable_hs(card);
		if (err > 0)
			mmc_set_timing(card->host, MMC_TIMING_SD_HS);
		else if (err)
			goto remove;

		/*
		 * Change to the card's maximum speed.
		 */
		mmc_set_clock(host, mmc_sdio_get_max_clock(card));

		/*
		 * Switch to wider bus (if supported).
		 */
		err = sdio_enable_4bit_bus(card);
		if (err)
			goto remove;
	}

	if (host->caps2 & MMC_CAP2_AVOID_3_3V &&
	    host->ios.signal_voltage == MMC_SIGNAL_VOLTAGE_330) {
		pr_err("%s: Host failed to negotiate down from 3.3V\n",
			mmc_hostname(host));
		err = -EINVAL;
		goto remove;
	}
finish:
	if (!oldcard)
		host->card = card;
	return 0;

remove:
	if (!oldcard)
		mmc_remove_card(card);

err:
	return err;
}