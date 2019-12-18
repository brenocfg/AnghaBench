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
struct TYPE_4__ {struct mlx5_cmd_stats* stats; } ;
struct TYPE_3__ {struct dentry* dbg_root; struct dentry* cmdif_debugfs; } ;
struct mlx5_core_dev {TYPE_2__ cmd; TYPE_1__ priv; } ;
struct mlx5_cmd_stats {int /*<<< orphan*/  n; void* root; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct mlx5_cmd_stats*) ; 
 void* debugfs_create_dir (char const*,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,void*,struct mlx5_cmd_stats*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u64 (char*,int,void*,int /*<<< orphan*/ *) ; 
 char* mlx5_command_str (int) ; 
 int /*<<< orphan*/  stats_fops ; 
 scalar_t__ strcmp (char const*,char*) ; 

void mlx5_cmdif_debugfs_init(struct mlx5_core_dev *dev)
{
	struct mlx5_cmd_stats *stats;
	struct dentry **cmd;
	const char *namep;
	int i;

	cmd = &dev->priv.cmdif_debugfs;
	*cmd = debugfs_create_dir("commands", dev->priv.dbg_root);

	for (i = 0; i < ARRAY_SIZE(dev->cmd.stats); i++) {
		stats = &dev->cmd.stats[i];
		namep = mlx5_command_str(i);
		if (strcmp(namep, "unknown command opcode")) {
			stats->root = debugfs_create_dir(namep, *cmd);

			debugfs_create_file("average", 0400, stats->root, stats,
					    &stats_fops);
			debugfs_create_u64("n", 0400, stats->root, &stats->n);
		}
	}
}