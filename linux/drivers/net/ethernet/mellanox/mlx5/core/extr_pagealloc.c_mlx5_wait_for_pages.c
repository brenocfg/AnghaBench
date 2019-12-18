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
struct mlx5_core_dev {scalar_t__ state; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MAX_RECLAIM_VFS_PAGES_TIME_MSECS ; 
 scalar_t__ MLX5_DEVICE_STATE_INTERNAL_ERROR ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,...) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,...) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

int mlx5_wait_for_pages(struct mlx5_core_dev *dev, int *pages)
{
	unsigned long end = jiffies + msecs_to_jiffies(MAX_RECLAIM_VFS_PAGES_TIME_MSECS);
	int prev_pages = *pages;

	/* In case of internal error we will free the pages manually later */
	if (dev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR) {
		mlx5_core_warn(dev, "Skipping wait for vf pages stage");
		return 0;
	}

	mlx5_core_dbg(dev, "Waiting for %d pages\n", prev_pages);
	while (*pages) {
		if (time_after(jiffies, end)) {
			mlx5_core_warn(dev, "aborting while there are %d pending pages\n", *pages);
			return -ETIMEDOUT;
		}
		if (*pages < prev_pages) {
			end = jiffies + msecs_to_jiffies(MAX_RECLAIM_VFS_PAGES_TIME_MSECS);
			prev_pages = *pages;
		}
		msleep(50);
	}

	mlx5_core_dbg(dev, "All pages received\n");
	return 0;
}