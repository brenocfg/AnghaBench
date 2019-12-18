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
struct mtd_info {int size; int /*<<< orphan*/  index; } ;
struct mtd_blktrans_ops {int dummy; } ;
struct mtd_blktrans_dev {int size; int readonly; struct mtd_blktrans_ops* tr; int /*<<< orphan*/  devnum; struct mtd_info* mtd; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ add_mtd_blktrans_dev (struct mtd_blktrans_dev*) ; 
 int /*<<< orphan*/  kfree (struct mtd_blktrans_dev*) ; 
 struct mtd_blktrans_dev* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtdblock_add_mtd(struct mtd_blktrans_ops *tr, struct mtd_info *mtd)
{
	struct mtd_blktrans_dev *dev = kzalloc(sizeof(*dev), GFP_KERNEL);

	if (!dev)
		return;

	dev->mtd = mtd;
	dev->devnum = mtd->index;

	dev->size = mtd->size >> 9;
	dev->tr = tr;
	dev->readonly = 1;

	if (add_mtd_blktrans_dev(dev))
		kfree(dev);
}