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
struct TYPE_2__ {int /*<<< orphan*/  cmdq_en; } ;
struct mmc_card {TYPE_1__ ext_csd; scalar_t__ reenable_cmdq; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 unsigned int EXT_CSD_PART_CONFIG_ACC_RPMB ; 
 int mmc_cmdq_enable (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_retune_unpause (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmc_blk_part_switch_post(struct mmc_card *card,
				    unsigned int part_type)
{
	int ret = 0;

	if (part_type == EXT_CSD_PART_CONFIG_ACC_RPMB) {
		mmc_retune_unpause(card->host);
		if (card->reenable_cmdq && !card->ext_csd.cmdq_en)
			ret = mmc_cmdq_enable(card);
	}

	return ret;
}