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
struct TYPE_4__ {struct dentry* cmdif_debugfs; struct dentry* dbg_root; } ;
struct TYPE_3__ {struct mlx5_cmd_stats* stats; } ;
struct mlx5_core_dev {TYPE_2__ priv; TYPE_1__ cmd; } ;
struct mlx5_cmd_stats {int /*<<< orphan*/  count; int /*<<< orphan*/  n; void* root; int /*<<< orphan*/  avg; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct mlx5_cmd_stats*) ; 
 int ENOMEM ; 
 void* debugfs_create_dir (char const*,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,void*,struct mlx5_cmd_stats*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u64 (char*,int,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (struct dentry*) ; 
 char* mlx5_command_str (int) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,...) ; 
 int /*<<< orphan*/  mlx5_debugfs_root ; 
 int /*<<< orphan*/  stats_fops ; 
 scalar_t__ strcmp (char const*,char*) ; 

int mlx5_cmdif_debugfs_init(struct mlx5_core_dev *dev)
{
	struct mlx5_cmd_stats *stats;
	struct dentry **cmd;
	const char *namep;
	int err;
	int i;

	if (!mlx5_debugfs_root)
		return 0;

	cmd = &dev->priv.cmdif_debugfs;
	*cmd = debugfs_create_dir("commands", dev->priv.dbg_root);
	if (!*cmd)
		return -ENOMEM;

	for (i = 0; i < ARRAY_SIZE(dev->cmd.stats); i++) {
		stats = &dev->cmd.stats[i];
		namep = mlx5_command_str(i);
		if (strcmp(namep, "unknown command opcode")) {
			stats->root = debugfs_create_dir(namep, *cmd);
			if (!stats->root) {
				mlx5_core_warn(dev, "failed adding command %d\n",
					       i);
				err = -ENOMEM;
				goto out;
			}

			stats->avg = debugfs_create_file("average", 0400,
							 stats->root, stats,
							 &stats_fops);
			if (!stats->avg) {
				mlx5_core_warn(dev, "failed creating debugfs file\n");
				err = -ENOMEM;
				goto out;
			}

			stats->count = debugfs_create_u64("n", 0400,
							  stats->root,
							  &stats->n);
			if (!stats->count) {
				mlx5_core_warn(dev, "failed creating debugfs file\n");
				err = -ENOMEM;
				goto out;
			}
		}
	}

	return 0;
out:
	debugfs_remove_recursive(dev->priv.cmdif_debugfs);
	return err;
}