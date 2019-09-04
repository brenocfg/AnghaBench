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
struct mlx5_ib_dev {int /*<<< orphan*/  flow_db; TYPE_2__* mdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  eswitch; } ;
struct TYPE_4__ {TYPE_1__ priv; } ;

/* Variables and functions */
 int EINVAL ; 
 struct mlx5_ib_dev* mlx5_ib_get_uplink_ibdev (int /*<<< orphan*/ ) ; 

int mlx5_ib_stage_rep_flow_db_init(struct mlx5_ib_dev *dev)
{
	struct mlx5_ib_dev *nic_dev;

	nic_dev = mlx5_ib_get_uplink_ibdev(dev->mdev->priv.eswitch);

	if (!nic_dev)
		return -EINVAL;

	dev->flow_db = nic_dev->flow_db;

	return 0;
}