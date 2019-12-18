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
struct mlx5_core_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * lag_demux_ft; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_cmd_destroy_vport_lag (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_destroy_flow_table (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5_eth_lag_cleanup(struct mlx5_ib_dev *dev)
{
	struct mlx5_core_dev *mdev = dev->mdev;

	if (dev->lag_active) {
		dev->lag_active = false;

		mlx5_destroy_flow_table(dev->flow_db->lag_demux_ft);
		dev->flow_db->lag_demux_ft = NULL;

		mlx5_cmd_destroy_vport_lag(mdev);
	}
}