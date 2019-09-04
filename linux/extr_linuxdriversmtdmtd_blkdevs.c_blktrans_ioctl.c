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
struct mtd_blktrans_dev {int /*<<< orphan*/  lock; TYPE_1__* tr; int /*<<< orphan*/  mtd; } ;
struct block_device {int /*<<< orphan*/  bd_disk; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {int (* flush ) (struct mtd_blktrans_dev*) ;} ;

/* Variables and functions */
#define  BLKFLSBUF 128 
 int ENOTTY ; 
 int ENXIO ; 
 struct mtd_blktrans_dev* blktrans_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blktrans_dev_put (struct mtd_blktrans_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct mtd_blktrans_dev*) ; 

__attribute__((used)) static int blktrans_ioctl(struct block_device *bdev, fmode_t mode,
			      unsigned int cmd, unsigned long arg)
{
	struct mtd_blktrans_dev *dev = blktrans_dev_get(bdev->bd_disk);
	int ret = -ENXIO;

	if (!dev)
		return ret;

	mutex_lock(&dev->lock);

	if (!dev->mtd)
		goto unlock;

	switch (cmd) {
	case BLKFLSBUF:
		ret = dev->tr->flush ? dev->tr->flush(dev) : 0;
		break;
	default:
		ret = -ENOTTY;
	}
unlock:
	mutex_unlock(&dev->lock);
	blktrans_dev_put(dev);
	return ret;
}