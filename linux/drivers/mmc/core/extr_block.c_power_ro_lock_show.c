#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int boot_ro_lock; } ;
struct mmc_card {TYPE_2__ ext_csd; } ;
struct TYPE_3__ {struct mmc_card* card; } ;
struct mmc_blk_data {TYPE_1__ queue; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EXT_CSD_BOOT_WP_B_PERM_WP_EN ; 
 int EXT_CSD_BOOT_WP_B_PWR_WP_EN ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dev_to_disk (struct device*) ; 
 struct mmc_blk_data* mmc_blk_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_blk_put (struct mmc_blk_data*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t power_ro_lock_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	int ret;
	struct mmc_blk_data *md = mmc_blk_get(dev_to_disk(dev));
	struct mmc_card *card = md->queue.card;
	int locked = 0;

	if (card->ext_csd.boot_ro_lock & EXT_CSD_BOOT_WP_B_PERM_WP_EN)
		locked = 2;
	else if (card->ext_csd.boot_ro_lock & EXT_CSD_BOOT_WP_B_PWR_WP_EN)
		locked = 1;

	ret = snprintf(buf, PAGE_SIZE, "%d\n", locked);

	mmc_blk_put(md);

	return ret;
}