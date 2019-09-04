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
struct TYPE_2__ {scalar_t__ cache_size; int cache_ctrl; } ;
struct mmc_card {int /*<<< orphan*/  host; TYPE_1__ ext_csd; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT_CSD_CMD_SET_NORMAL ; 
 int /*<<< orphan*/  EXT_CSD_FLUSH_CACHE ; 
 scalar_t__ mmc_card_mmc (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int mmc_switch (struct mmc_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

int mmc_flush_cache(struct mmc_card *card)
{
	int err = 0;

	if (mmc_card_mmc(card) &&
			(card->ext_csd.cache_size > 0) &&
			(card->ext_csd.cache_ctrl & 1)) {
		err = mmc_switch(card, EXT_CSD_CMD_SET_NORMAL,
				EXT_CSD_FLUSH_CACHE, 1, 0);
		if (err)
			pr_err("%s: cache flush error %d\n",
					mmc_hostname(card->host), err);
	}

	return err;
}