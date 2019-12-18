#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* mtd; } ;
struct partition {int total_blocks; TYPE_3__* blocks; TYPE_3__* header_cache; int /*<<< orphan*/  sector_map; TYPE_2__ mbd; } ;
struct mtd_blktrans_dev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  erases; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_mtd_blktrans_dev (struct mtd_blktrans_dev*) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rfd_ftl_remove_dev(struct mtd_blktrans_dev *dev)
{
	struct partition *part = (struct partition*)dev;
	int i;

	for (i=0; i<part->total_blocks; i++) {
		pr_debug("rfd_ftl_remove_dev:'%s': erase unit #%02d: %d erases\n",
			part->mbd.mtd->name, i, part->blocks[i].erases);
	}

	del_mtd_blktrans_dev(dev);
	vfree(part->sector_map);
	kfree(part->header_cache);
	kfree(part->blocks);
}