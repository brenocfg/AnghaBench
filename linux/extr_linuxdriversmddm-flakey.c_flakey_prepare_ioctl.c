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
struct flakey_c {scalar_t__ start; TYPE_1__* dev; } ;
struct dm_target {scalar_t__ len; struct flakey_c* private; } ;
struct block_device {int /*<<< orphan*/  bd_inode; } ;
struct TYPE_2__ {struct block_device* bdev; } ;

/* Variables and functions */
 int SECTOR_SHIFT ; 
 scalar_t__ i_size_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flakey_prepare_ioctl(struct dm_target *ti, struct block_device **bdev)
{
	struct flakey_c *fc = ti->private;

	*bdev = fc->dev->bdev;

	/*
	 * Only pass ioctls through if the device sizes match exactly.
	 */
	if (fc->start ||
	    ti->len != i_size_read((*bdev)->bd_inode) >> SECTOR_SHIFT)
		return 1;
	return 0;
}