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
struct TYPE_3__ {int /*<<< orphan*/  dbg_root; } ;
struct mlx5_cmd_debug {int /*<<< orphan*/  dbg_root; int /*<<< orphan*/  status; } ;
struct TYPE_4__ {struct mlx5_cmd_debug dbg; } ;
struct mlx5_core_dev {TYPE_1__ priv; TYPE_2__ cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u8 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dfops ; 
 int /*<<< orphan*/  fops ; 
 int /*<<< orphan*/  mlx5_cmdif_debugfs_init (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  olfops ; 

__attribute__((used)) static void create_debugfs_files(struct mlx5_core_dev *dev)
{
	struct mlx5_cmd_debug *dbg = &dev->cmd.dbg;

	dbg->dbg_root = debugfs_create_dir("cmd", dev->priv.dbg_root);

	debugfs_create_file("in", 0400, dbg->dbg_root, dev, &dfops);
	debugfs_create_file("out", 0200, dbg->dbg_root, dev, &dfops);
	debugfs_create_file("out_len", 0600, dbg->dbg_root, dev, &olfops);
	debugfs_create_u8("status", 0600, dbg->dbg_root, &dbg->status);
	debugfs_create_file("run", 0200, dbg->dbg_root, dev, &fops);

	mlx5_cmdif_debugfs_init(dev);
}