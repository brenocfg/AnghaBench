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
struct md_rdev {struct block_device* bdev; } ;
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int FMODE_EXCL ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 scalar_t__ IS_ERR (struct block_device*) ; 
 int PTR_ERR (struct block_device*) ; 
 int /*<<< orphan*/  __bdevname (int /*<<< orphan*/ ,char*) ; 
 struct block_device* blkdev_get_by_dev (int /*<<< orphan*/ ,int,struct md_rdev*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lock_rdev(struct md_rdev *rdev, dev_t dev, int shared)
{
	int err = 0;
	struct block_device *bdev;
	char b[BDEVNAME_SIZE];

	bdev = blkdev_get_by_dev(dev, FMODE_READ|FMODE_WRITE|FMODE_EXCL,
				 shared ? (struct md_rdev *)lock_rdev : rdev);
	if (IS_ERR(bdev)) {
		pr_warn("md: could not open %s.\n", __bdevname(dev, b));
		return PTR_ERR(bdev);
	}
	rdev->bdev = bdev;
	return err;
}