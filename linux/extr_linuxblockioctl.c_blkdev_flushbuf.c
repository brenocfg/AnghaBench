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
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EACCES ; 
 int __blkdev_driver_ioctl (struct block_device*,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsync_bdev (struct block_device*) ; 
 int /*<<< orphan*/  invalidate_bdev (struct block_device*) ; 
 int /*<<< orphan*/  is_unrecognized_ioctl (int) ; 

__attribute__((used)) static int blkdev_flushbuf(struct block_device *bdev, fmode_t mode,
		unsigned cmd, unsigned long arg)
{
	int ret;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	ret = __blkdev_driver_ioctl(bdev, mode, cmd, arg);
	if (!is_unrecognized_ioctl(ret))
		return ret;

	fsync_bdev(bdev);
	invalidate_bdev(bdev);
	return 0;
}