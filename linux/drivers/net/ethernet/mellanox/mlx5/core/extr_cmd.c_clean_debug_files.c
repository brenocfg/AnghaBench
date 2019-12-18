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
struct mlx5_cmd_debug {int /*<<< orphan*/  dbg_root; } ;
struct TYPE_2__ {struct mlx5_cmd_debug dbg; } ;
struct mlx5_core_dev {TYPE_1__ cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_cmdif_debugfs_cleanup (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_debugfs_root ; 

__attribute__((used)) static void clean_debug_files(struct mlx5_core_dev *dev)
{
	struct mlx5_cmd_debug *dbg = &dev->cmd.dbg;

	if (!mlx5_debugfs_root)
		return;

	mlx5_cmdif_debugfs_cleanup(dev);
	debugfs_remove_recursive(dbg->dbg_root);
}