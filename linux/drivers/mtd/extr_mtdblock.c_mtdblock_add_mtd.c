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
struct TYPE_2__ {int size; int readonly; struct mtd_blktrans_ops* tr; int /*<<< orphan*/  devnum; struct mtd_info* mtd; } ;
struct mtdblk_dev {TYPE_1__ mbd; } ;
struct mtd_info {int size; int flags; int /*<<< orphan*/  index; } ;
struct mtd_blktrans_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MTD_WRITEABLE ; 
 scalar_t__ add_mtd_blktrans_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct mtdblk_dev*) ; 
 struct mtdblk_dev* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtdblock_add_mtd(struct mtd_blktrans_ops *tr, struct mtd_info *mtd)
{
	struct mtdblk_dev *dev = kzalloc(sizeof(*dev), GFP_KERNEL);

	if (!dev)
		return;

	dev->mbd.mtd = mtd;
	dev->mbd.devnum = mtd->index;

	dev->mbd.size = mtd->size >> 9;
	dev->mbd.tr = tr;

	if (!(mtd->flags & MTD_WRITEABLE))
		dev->mbd.readonly = 1;

	if (add_mtd_blktrans_dev(&dev->mbd))
		kfree(dev);
}