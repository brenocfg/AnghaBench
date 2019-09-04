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
struct mmc_card {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mmc_card_clr_doing_bkops (struct mmc_card*) ; 
 int mmc_interrupt_hpi (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_retune_release (int /*<<< orphan*/ ) ; 

int mmc_stop_bkops(struct mmc_card *card)
{
	int err = 0;

	err = mmc_interrupt_hpi(card);

	/*
	 * If err is EINVAL, we can't issue an HPI.
	 * It should complete the BKOPS.
	 */
	if (!err || (err == -EINVAL)) {
		mmc_card_clr_doing_bkops(card);
		mmc_retune_release(card->host);
		err = 0;
	}

	return err;
}