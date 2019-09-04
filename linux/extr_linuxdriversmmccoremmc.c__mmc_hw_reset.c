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
struct mmc_host {int caps; TYPE_1__* ops; int /*<<< orphan*/  f_init; struct mmc_card* card; } ;
struct mmc_card {int /*<<< orphan*/  ocr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* hw_reset ) (struct mmc_host*) ;} ;

/* Variables and functions */
 int MMC_CAP_HW_RESET ; 
 scalar_t__ mmc_can_reset (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_flush_cache (struct mmc_card*) ; 
 int mmc_init_card (struct mmc_host*,int /*<<< orphan*/ ,struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_power_cycle (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_pwrseq_reset (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_set_clock (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_set_initial_state (struct mmc_host*) ; 
 int /*<<< orphan*/  stub1 (struct mmc_host*) ; 

__attribute__((used)) static int _mmc_hw_reset(struct mmc_host *host)
{
	struct mmc_card *card = host->card;

	/*
	 * In the case of recovery, we can't expect flushing the cache to work
	 * always, but we have a go and ignore errors.
	 */
	mmc_flush_cache(host->card);

	if ((host->caps & MMC_CAP_HW_RESET) && host->ops->hw_reset &&
	     mmc_can_reset(card)) {
		/* If the card accept RST_n signal, send it. */
		mmc_set_clock(host, host->f_init);
		host->ops->hw_reset(host);
		/* Set initial state and call mmc_set_ios */
		mmc_set_initial_state(host);
	} else {
		/* Do a brute force power cycle */
		mmc_power_cycle(host, card->ocr);
		mmc_pwrseq_reset(host);
	}
	return mmc_init_card(host, card->ocr, card);
}