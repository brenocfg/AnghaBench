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
struct TYPE_2__ {int vfs_pages; int /*<<< orphan*/  name; } ;
struct mlx5_core_dev {scalar_t__ state; TYPE_1__ priv; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MAX_RECLAIM_VFS_PAGES_TIME_MSECS ; 
 scalar_t__ MLX5_DEVICE_STATE_INTERNAL_ERROR ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,int,...) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,...) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

int mlx5_wait_for_vf_pages(struct mlx5_core_dev *dev)
{
	unsigned long end = jiffies + msecs_to_jiffies(MAX_RECLAIM_VFS_PAGES_TIME_MSECS);
	int prev_vfs_pages = dev->priv.vfs_pages;

	/* In case of internal error we will free the pages manually later */
	if (dev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR) {
		mlx5_core_warn(dev, "Skipping wait for vf pages stage");
		return 0;
	}

	mlx5_core_dbg(dev, "Waiting for %d pages from %s\n", prev_vfs_pages,
		      dev->priv.name);
	while (dev->priv.vfs_pages) {
		if (time_after(jiffies, end)) {
			mlx5_core_warn(dev, "aborting while there are %d pending pages\n", dev->priv.vfs_pages);
			return -ETIMEDOUT;
		}
		if (dev->priv.vfs_pages < prev_vfs_pages) {
			end = jiffies + msecs_to_jiffies(MAX_RECLAIM_VFS_PAGES_TIME_MSECS);
			prev_vfs_pages = dev->priv.vfs_pages;
		}
		msleep(50);
	}

	mlx5_core_dbg(dev, "All pages received from %s\n", dev->priv.name);
	return 0;
}