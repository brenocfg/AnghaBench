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
struct log_writes_c {struct dm_dev* dev; } ;
struct dm_target {scalar_t__ len; struct log_writes_c* private; } ;
struct dm_dev {struct block_device* bdev; } ;
struct block_device {int /*<<< orphan*/  bd_inode; } ;

/* Variables and functions */
 int SECTOR_SHIFT ; 
 scalar_t__ i_size_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int log_writes_prepare_ioctl(struct dm_target *ti,
				    struct block_device **bdev)
{
	struct log_writes_c *lc = ti->private;
	struct dm_dev *dev = lc->dev;

	*bdev = dev->bdev;
	/*
	 * Only pass ioctls through if the device sizes match exactly.
	 */
	if (ti->len != i_size_read(dev->bdev->bd_inode) >> SECTOR_SHIFT)
		return 1;
	return 0;
}