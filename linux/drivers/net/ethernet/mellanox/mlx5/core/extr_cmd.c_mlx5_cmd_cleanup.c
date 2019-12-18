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
struct mlx5_cmd {int /*<<< orphan*/  pool; int /*<<< orphan*/  wq; } ;
struct mlx5_core_dev {struct mlx5_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  clean_debug_files (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  destroy_msg_cache (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cmd_page (struct mlx5_core_dev*,struct mlx5_cmd*) ; 

void mlx5_cmd_cleanup(struct mlx5_core_dev *dev)
{
	struct mlx5_cmd *cmd = &dev->cmd;

	clean_debug_files(dev);
	destroy_workqueue(cmd->wq);
	destroy_msg_cache(dev);
	free_cmd_page(dev, cmd);
	dma_pool_destroy(cmd->pool);
}