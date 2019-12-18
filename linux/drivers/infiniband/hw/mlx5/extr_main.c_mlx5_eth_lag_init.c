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
struct mlx5_ib_dev {int lag_active; TYPE_1__* flow_db; struct mlx5_core_dev* mdev; } ;
struct mlx5_flow_table {int dummy; } ;
struct mlx5_flow_namespace {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_2__ {struct mlx5_flow_table* lag_demux_ft; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx5_flow_table*) ; 
 int /*<<< orphan*/  MLX5_FLOW_NAMESPACE_LAG ; 
 int PTR_ERR (struct mlx5_flow_table*) ; 
 int mlx5_cmd_create_vport_lag (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cmd_destroy_vport_lag (struct mlx5_core_dev*) ; 
 struct mlx5_flow_table* mlx5_create_lag_demux_flow_table (struct mlx5_flow_namespace*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5_flow_namespace* mlx5_get_flow_namespace (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_lag_is_roce (struct mlx5_core_dev*) ; 

__attribute__((used)) static int mlx5_eth_lag_init(struct mlx5_ib_dev *dev)
{
	struct mlx5_core_dev *mdev = dev->mdev;
	struct mlx5_flow_namespace *ns = mlx5_get_flow_namespace(mdev,
								 MLX5_FLOW_NAMESPACE_LAG);
	struct mlx5_flow_table *ft;
	int err;

	if (!ns || !mlx5_lag_is_roce(mdev))
		return 0;

	err = mlx5_cmd_create_vport_lag(mdev);
	if (err)
		return err;

	ft = mlx5_create_lag_demux_flow_table(ns, 0, 0);
	if (IS_ERR(ft)) {
		err = PTR_ERR(ft);
		goto err_destroy_vport_lag;
	}

	dev->flow_db->lag_demux_ft = ft;
	dev->lag_active = true;
	return 0;

err_destroy_vport_lag:
	mlx5_cmd_destroy_vport_lag(mdev);
	return err;
}