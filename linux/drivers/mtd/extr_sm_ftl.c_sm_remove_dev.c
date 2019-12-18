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
struct sm_ftl {int zone_count; struct sm_ftl* cache_data; struct sm_ftl* zones; struct sm_ftl* cis_buffer; int /*<<< orphan*/  free_sectors; struct sm_ftl* lba_to_phys_table; int /*<<< orphan*/  initialized; int /*<<< orphan*/ * trans; } ;
struct mtd_blktrans_dev {struct sm_ftl* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_mtd_blktrans_dev (struct mtd_blktrans_dev*) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct sm_ftl*) ; 
 int /*<<< orphan*/  sm_delete_sysfs_attributes (struct sm_ftl*) ; 

__attribute__((used)) static void sm_remove_dev(struct mtd_blktrans_dev *dev)
{
	struct sm_ftl *ftl = dev->priv;
	int i;

	del_mtd_blktrans_dev(dev);
	ftl->trans = NULL;

	for (i = 0 ; i < ftl->zone_count; i++) {

		if (!ftl->zones[i].initialized)
			continue;

		kfree(ftl->zones[i].lba_to_phys_table);
		kfifo_free(&ftl->zones[i].free_sectors);
	}

	sm_delete_sysfs_attributes(ftl);
	kfree(ftl->cis_buffer);
	kfree(ftl->zones);
	kfree(ftl->cache_data);
	kfree(ftl);
}