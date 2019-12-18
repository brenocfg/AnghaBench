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
struct mmc_card {scalar_t__ type; int /*<<< orphan*/  complete_wq; int /*<<< orphan*/  dev; int /*<<< orphan*/  host; } ;
struct mmc_blk_data {scalar_t__ part_curr; scalar_t__ part_type; } ;

/* Variables and functions */
 scalar_t__ MMC_TYPE_SD_COMBO ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 struct mmc_blk_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_blk_part_switch (struct mmc_card*,scalar_t__) ; 
 int /*<<< orphan*/  mmc_blk_remove_debugfs (struct mmc_card*,struct mmc_blk_data*) ; 
 int /*<<< orphan*/  mmc_blk_remove_parts (struct mmc_card*,struct mmc_blk_data*) ; 
 int /*<<< orphan*/  mmc_blk_remove_req (struct mmc_blk_data*) ; 
 int /*<<< orphan*/  mmc_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_release_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mmc_blk_remove(struct mmc_card *card)
{
	struct mmc_blk_data *md = dev_get_drvdata(&card->dev);

	mmc_blk_remove_debugfs(card, md);
	mmc_blk_remove_parts(card, md);
	pm_runtime_get_sync(&card->dev);
	if (md->part_curr != md->part_type) {
		mmc_claim_host(card->host);
		mmc_blk_part_switch(card, md->part_type);
		mmc_release_host(card->host);
	}
	if (card->type != MMC_TYPE_SD_COMBO)
		pm_runtime_disable(&card->dev);
	pm_runtime_put_noidle(&card->dev);
	mmc_blk_remove_req(md);
	dev_set_drvdata(&card->dev, NULL);
	destroy_workqueue(card->complete_wq);
}