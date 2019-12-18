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
struct TYPE_2__ {int stopped; int /*<<< orphan*/  wq; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  delay_timer; TYPE_1__ cache; int /*<<< orphan*/  async_ctx; } ;

/* Variables and functions */
 int MAX_MR_CACHE_ENTRIES ; 
 int /*<<< orphan*/  clean_keys (struct mlx5_ib_dev*,int) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_cmd_cleanup_async_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_mr_cache_debugfs_cleanup (struct mlx5_ib_dev*) ; 

int mlx5_mr_cache_cleanup(struct mlx5_ib_dev *dev)
{
	int i;

	if (!dev->cache.wq)
		return 0;

	dev->cache.stopped = 1;
	flush_workqueue(dev->cache.wq);

	mlx5_mr_cache_debugfs_cleanup(dev);
	mlx5_cmd_cleanup_async_ctx(&dev->async_ctx);

	for (i = 0; i < MAX_MR_CACHE_ENTRIES; i++)
		clean_keys(dev, i);

	destroy_workqueue(dev->cache.wq);
	del_timer_sync(&dev->delay_timer);

	return 0;
}