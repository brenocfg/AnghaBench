#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct mlx5_ib_dev {TYPE_1__* port; } ;
struct mlx5_ib_dbg_cc_params {TYPE_3__* params; int /*<<< orphan*/  root; } ;
struct TYPE_5__ {int /*<<< orphan*/  dbg_root; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;
struct TYPE_6__ {int offset; int port_num; int /*<<< orphan*/  dentry; struct mlx5_ib_dev* dev; } ;
struct TYPE_4__ {struct mlx5_ib_dbg_cc_params* dbg_cc_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int MLX5_IB_DBG_CC_MAX ; 
 int /*<<< orphan*/  cc_modify_allowed ; 
 int /*<<< orphan*/  cc_query_allowed ; 
 int /*<<< orphan*/  dbg_cc_fops ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 struct mlx5_ib_dbg_cc_params* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_debugfs_root ; 
 int /*<<< orphan*/  mlx5_ib_cleanup_cong_debugfs (struct mlx5_ib_dev*,int) ; 
 int /*<<< orphan*/ * mlx5_ib_dbg_cc_name ; 
 struct mlx5_core_dev* mlx5_ib_get_native_port_mdev (struct mlx5_ib_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_put_native_port_mdev (struct mlx5_ib_dev*,int) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*) ; 

void mlx5_ib_init_cong_debugfs(struct mlx5_ib_dev *dev, u8 port_num)
{
	struct mlx5_ib_dbg_cc_params *dbg_cc_params;
	struct mlx5_core_dev *mdev;
	int i;

	if (!mlx5_debugfs_root)
		return;

	/* Takes a 1-based port number */
	mdev = mlx5_ib_get_native_port_mdev(dev, port_num + 1, NULL);
	if (!mdev)
		return;

	if (!MLX5_CAP_GEN(mdev, cc_query_allowed) ||
	    !MLX5_CAP_GEN(mdev, cc_modify_allowed))
		goto put_mdev;

	dbg_cc_params = kzalloc(sizeof(*dbg_cc_params), GFP_KERNEL);
	if (!dbg_cc_params)
		goto err;

	dev->port[port_num].dbg_cc_params = dbg_cc_params;

	dbg_cc_params->root = debugfs_create_dir("cc_params",
						 mdev->priv.dbg_root);

	for (i = 0; i < MLX5_IB_DBG_CC_MAX; i++) {
		dbg_cc_params->params[i].offset = i;
		dbg_cc_params->params[i].dev = dev;
		dbg_cc_params->params[i].port_num = port_num;
		dbg_cc_params->params[i].dentry =
			debugfs_create_file(mlx5_ib_dbg_cc_name[i],
					    0600, dbg_cc_params->root,
					    &dbg_cc_params->params[i],
					    &dbg_cc_fops);
	}

put_mdev:
	mlx5_ib_put_native_port_mdev(dev, port_num + 1);
	return;

err:
	mlx5_ib_warn(dev, "cong debugfs failure\n");
	mlx5_ib_cleanup_cong_debugfs(dev, port_num);
	mlx5_ib_put_native_port_mdev(dev, port_num + 1);

	/*
	 * We don't want to fail driver if debugfs failed to initialize,
	 * so we are not forwarding error to the user.
	 */
	return;
}