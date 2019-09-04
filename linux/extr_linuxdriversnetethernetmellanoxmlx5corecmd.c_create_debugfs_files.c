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
struct TYPE_4__ {int /*<<< orphan*/  dbg_root; } ;
struct mlx5_cmd_debug {void* dbg_run; int /*<<< orphan*/  dbg_root; int /*<<< orphan*/  dbg_status; int /*<<< orphan*/  status; void* dbg_outlen; void* dbg_out; void* dbg_in; } ;
struct TYPE_3__ {struct mlx5_cmd_debug dbg; } ;
struct mlx5_core_dev {TYPE_2__ priv; TYPE_1__ cmd; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  clean_debug_files (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 void* debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u8 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dfops ; 
 int /*<<< orphan*/  fops ; 
 int /*<<< orphan*/  mlx5_cmdif_debugfs_init (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_debugfs_root ; 
 int /*<<< orphan*/  olfops ; 

__attribute__((used)) static int create_debugfs_files(struct mlx5_core_dev *dev)
{
	struct mlx5_cmd_debug *dbg = &dev->cmd.dbg;
	int err = -ENOMEM;

	if (!mlx5_debugfs_root)
		return 0;

	dbg->dbg_root = debugfs_create_dir("cmd", dev->priv.dbg_root);
	if (!dbg->dbg_root)
		return err;

	dbg->dbg_in = debugfs_create_file("in", 0400, dbg->dbg_root,
					  dev, &dfops);
	if (!dbg->dbg_in)
		goto err_dbg;

	dbg->dbg_out = debugfs_create_file("out", 0200, dbg->dbg_root,
					   dev, &dfops);
	if (!dbg->dbg_out)
		goto err_dbg;

	dbg->dbg_outlen = debugfs_create_file("out_len", 0600, dbg->dbg_root,
					      dev, &olfops);
	if (!dbg->dbg_outlen)
		goto err_dbg;

	dbg->dbg_status = debugfs_create_u8("status", 0600, dbg->dbg_root,
					    &dbg->status);
	if (!dbg->dbg_status)
		goto err_dbg;

	dbg->dbg_run = debugfs_create_file("run", 0200, dbg->dbg_root, dev, &fops);
	if (!dbg->dbg_run)
		goto err_dbg;

	mlx5_cmdif_debugfs_init(dev);

	return 0;

err_dbg:
	clean_debug_files(dev);
	return err;
}