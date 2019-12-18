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
struct mmc_host {int dummy; } ;
struct mmc_card {int dummy; } ;

/* Variables and functions */
 int mmc_app_send_scr (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_card_set_readonly (struct mmc_card*) ; 
 int mmc_decode_scr (struct mmc_card*) ; 
 scalar_t__ mmc_host_is_spi (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_init_erase (struct mmc_card*) ; 
 int mmc_read_ssr (struct mmc_card*) ; 
 int mmc_read_switch (struct mmc_card*) ; 
 int mmc_sd_get_ro (struct mmc_host*) ; 
 int mmc_spi_set_crc (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_spi_crc ; 

int mmc_sd_setup_card(struct mmc_host *host, struct mmc_card *card,
	bool reinit)
{
	int err;

	if (!reinit) {
		/*
		 * Fetch SCR from card.
		 */
		err = mmc_app_send_scr(card);
		if (err)
			return err;

		err = mmc_decode_scr(card);
		if (err)
			return err;

		/*
		 * Fetch and process SD Status register.
		 */
		err = mmc_read_ssr(card);
		if (err)
			return err;

		/* Erase init depends on CSD and SSR */
		mmc_init_erase(card);

		/*
		 * Fetch switch information from card.
		 */
		err = mmc_read_switch(card);
		if (err)
			return err;
	}

	/*
	 * For SPI, enable CRC as appropriate.
	 * This CRC enable is located AFTER the reading of the
	 * card registers because some SDHC cards are not able
	 * to provide valid CRCs for non-512-byte blocks.
	 */
	if (mmc_host_is_spi(host)) {
		err = mmc_spi_set_crc(host, use_spi_crc);
		if (err)
			return err;
	}

	/*
	 * Check if read-only switch is active.
	 */
	if (!reinit) {
		int ro = mmc_sd_get_ro(host);

		if (ro < 0) {
			pr_warn("%s: host does not support reading read-only switch, assuming write-enable\n",
				mmc_hostname(host));
		} else if (ro > 0) {
			mmc_card_set_readonly(card);
		}
	}

	return 0;
}