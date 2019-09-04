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
struct TYPE_2__ {scalar_t__ cmdq_en; } ;
struct mmc_card {int /*<<< orphan*/  dev; int /*<<< orphan*/  host; TYPE_1__ ext_csd; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mmc_card_mmc (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_card_sd (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_claim_host (int /*<<< orphan*/ ) ; 
 int mmc_cmdq_disable (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_release_host (int /*<<< orphan*/ ) ; 
 int mmc_test_register_dbgfs_file (struct mmc_card*) ; 

__attribute__((used)) static int mmc_test_probe(struct mmc_card *card)
{
	int ret;

	if (!mmc_card_mmc(card) && !mmc_card_sd(card))
		return -ENODEV;

	ret = mmc_test_register_dbgfs_file(card);
	if (ret)
		return ret;

	if (card->ext_csd.cmdq_en) {
		mmc_claim_host(card->host);
		ret = mmc_cmdq_disable(card);
		mmc_release_host(card->host);
		if (ret)
			return ret;
	}

	dev_info(&card->dev, "Card claimed for testing.\n");

	return 0;
}