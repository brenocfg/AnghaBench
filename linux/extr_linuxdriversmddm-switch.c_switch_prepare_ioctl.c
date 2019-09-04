#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct switch_ctx {TYPE_2__* path_list; } ;
struct dm_target {scalar_t__ len; struct switch_ctx* private; } ;
struct block_device {int /*<<< orphan*/  bd_inode; } ;
struct TYPE_4__ {scalar_t__ start; TYPE_1__* dmdev; } ;
struct TYPE_3__ {struct block_device* bdev; } ;

/* Variables and functions */
 int SECTOR_SHIFT ; 
 scalar_t__ i_size_read (int /*<<< orphan*/ ) ; 
 unsigned int switch_get_path_nr (struct switch_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int switch_prepare_ioctl(struct dm_target *ti, struct block_device **bdev)
{
	struct switch_ctx *sctx = ti->private;
	unsigned path_nr;

	path_nr = switch_get_path_nr(sctx, 0);

	*bdev = sctx->path_list[path_nr].dmdev->bdev;

	/*
	 * Only pass ioctls through if the device sizes match exactly.
	 */
	if (ti->len + sctx->path_list[path_nr].start !=
	    i_size_read((*bdev)->bd_inode) >> SECTOR_SHIFT)
		return 1;
	return 0;
}