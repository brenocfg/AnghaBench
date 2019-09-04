#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mmc_host {TYPE_1__* card; } ;
struct TYPE_4__ {int /*<<< orphan*/  ocr; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_card_clr_suspended (TYPE_1__*) ; 
 int /*<<< orphan*/  mmc_card_suspended (TYPE_1__*) ; 
 int /*<<< orphan*/  mmc_claim_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_power_up (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_release_host (struct mmc_host*) ; 
 int mmc_sd_init_card (struct mmc_host*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int _mmc_sd_resume(struct mmc_host *host)
{
	int err = 0;

	mmc_claim_host(host);

	if (!mmc_card_suspended(host->card))
		goto out;

	mmc_power_up(host, host->card->ocr);
	err = mmc_sd_init_card(host, host->card->ocr, host->card);
	mmc_card_clr_suspended(host->card);

out:
	mmc_release_host(host);
	return err;
}