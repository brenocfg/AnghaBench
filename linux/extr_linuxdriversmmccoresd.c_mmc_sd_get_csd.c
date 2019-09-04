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
struct mmc_card {int /*<<< orphan*/  raw_csd; } ;

/* Variables and functions */
 int mmc_decode_csd (struct mmc_card*) ; 
 int mmc_send_csd (struct mmc_card*,int /*<<< orphan*/ ) ; 

int mmc_sd_get_csd(struct mmc_host *host, struct mmc_card *card)
{
	int err;

	/*
	 * Fetch CSD from card.
	 */
	err = mmc_send_csd(card, card->raw_csd);
	if (err)
		return err;

	err = mmc_decode_csd(card);
	if (err)
		return err;

	return 0;
}