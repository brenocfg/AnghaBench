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
struct mmc_host {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_card_set_suspended (int /*<<< orphan*/ ) ; 
 scalar_t__ mmc_card_suspended (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_claim_host (struct mmc_host*) ; 
 int mmc_deselect_cards (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_host_is_spi (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_power_off (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_release_host (struct mmc_host*) ; 

__attribute__((used)) static int _mmc_sd_suspend(struct mmc_host *host)
{
	int err = 0;

	mmc_claim_host(host);

	if (mmc_card_suspended(host->card))
		goto out;

	if (!mmc_host_is_spi(host))
		err = mmc_deselect_cards(host);

	if (!err) {
		mmc_power_off(host);
		mmc_card_set_suspended(host->card);
	}

out:
	mmc_release_host(host);
	return err;
}