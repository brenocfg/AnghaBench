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
struct mmc_card {int nr_parts; TYPE_1__* part; } ;
struct mmc_blk_data {int dummy; } ;
struct TYPE_2__ {int area_type; int size; int /*<<< orphan*/  name; int /*<<< orphan*/  force_ro; int /*<<< orphan*/  part_cfg; } ;

/* Variables and functions */
 int MMC_BLK_DATA_AREA_RPMB ; 
 int mmc_blk_alloc_part (struct mmc_card*,struct mmc_blk_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mmc_blk_alloc_rpmb_part (struct mmc_card*,struct mmc_blk_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_card_mmc (struct mmc_card*) ; 

__attribute__((used)) static int mmc_blk_alloc_parts(struct mmc_card *card, struct mmc_blk_data *md)
{
	int idx, ret;

	if (!mmc_card_mmc(card))
		return 0;

	for (idx = 0; idx < card->nr_parts; idx++) {
		if (card->part[idx].area_type & MMC_BLK_DATA_AREA_RPMB) {
			/*
			 * RPMB partitions does not provide block access, they
			 * are only accessed using ioctl():s. Thus create
			 * special RPMB block devices that do not have a
			 * backing block queue for these.
			 */
			ret = mmc_blk_alloc_rpmb_part(card, md,
				card->part[idx].part_cfg,
				card->part[idx].size >> 9,
				card->part[idx].name);
			if (ret)
				return ret;
		} else if (card->part[idx].size) {
			ret = mmc_blk_alloc_part(card, md,
				card->part[idx].part_cfg,
				card->part[idx].size >> 9,
				card->part[idx].force_ro,
				card->part[idx].name,
				card->part[idx].area_type);
			if (ret)
				return ret;
		}
	}

	return 0;
}