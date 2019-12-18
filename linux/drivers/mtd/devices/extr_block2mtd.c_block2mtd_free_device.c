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
struct TYPE_4__ {struct block2mtd_dev* name; } ;
struct block2mtd_dev {TYPE_3__* blkdev; TYPE_1__ mtd; } ;
struct TYPE_6__ {TYPE_2__* bd_inode; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int FMODE_EXCL ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  blkdev_put (TYPE_3__*,int) ; 
 int /*<<< orphan*/  invalidate_mapping_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct block2mtd_dev*) ; 

__attribute__((used)) static void block2mtd_free_device(struct block2mtd_dev *dev)
{
	if (!dev)
		return;

	kfree(dev->mtd.name);

	if (dev->blkdev) {
		invalidate_mapping_pages(dev->blkdev->bd_inode->i_mapping,
					0, -1);
		blkdev_put(dev->blkdev, FMODE_READ|FMODE_WRITE|FMODE_EXCL);
	}

	kfree(dev);
}