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
struct mmc_host {TYPE_1__* card; } ;
struct mmc_blk_data {int reset_done; int /*<<< orphan*/  part_type; int /*<<< orphan*/  part_curr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 struct mmc_blk_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int mmc_blk_part_switch (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int mmc_hw_reset (struct mmc_host*) ; 

__attribute__((used)) static int mmc_blk_reset(struct mmc_blk_data *md, struct mmc_host *host,
			 int type)
{
	int err;

	if (md->reset_done & type)
		return -EEXIST;

	md->reset_done |= type;
	err = mmc_hw_reset(host);
	/* Ensure we switch back to the correct partition */
	if (err != -EOPNOTSUPP) {
		struct mmc_blk_data *main_md =
			dev_get_drvdata(&host->card->dev);
		int part_err;

		main_md->part_curr = main_md->part_type;
		part_err = mmc_blk_part_switch(host->card, md->part_type);
		if (part_err) {
			/*
			 * We have failed to get back into the correct
			 * partition, so we need to abort the whole request.
			 */
			return -ENODEV;
		}
	}
	return err;
}