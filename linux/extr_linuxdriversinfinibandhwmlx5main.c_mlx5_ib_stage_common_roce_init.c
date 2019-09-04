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
typedef  scalar_t__ u8 ;
struct TYPE_4__ {unsigned long long uverbs_ex_cmd_mask; int /*<<< orphan*/  destroy_rwq_ind_table; int /*<<< orphan*/  create_rwq_ind_table; int /*<<< orphan*/  destroy_wq; int /*<<< orphan*/  modify_wq; int /*<<< orphan*/  create_wq; int /*<<< orphan*/  get_netdev; } ;
struct mlx5_ib_dev {int num_ports; int /*<<< orphan*/  mdev; TYPE_2__ ib_dev; TYPE_1__* roce; } ;
struct TYPE_3__ {int native_port_num; int /*<<< orphan*/  last_port_state; struct mlx5_ib_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_PORT_DOWN ; 
 unsigned long long IB_USER_VERBS_EX_CMD_CREATE_RWQ_IND_TBL ; 
 unsigned long long IB_USER_VERBS_EX_CMD_CREATE_WQ ; 
 unsigned long long IB_USER_VERBS_EX_CMD_DESTROY_RWQ_IND_TBL ; 
 unsigned long long IB_USER_VERBS_EX_CMD_DESTROY_WQ ; 
 unsigned long long IB_USER_VERBS_EX_CMD_MODIFY_WQ ; 
 int mlx5_add_netdev_notifier (struct mlx5_ib_dev*,scalar_t__) ; 
 scalar_t__ mlx5_core_native_port_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_create_rwq_ind_table ; 
 int /*<<< orphan*/  mlx5_ib_create_wq ; 
 int /*<<< orphan*/  mlx5_ib_destroy_rwq_ind_table ; 
 int /*<<< orphan*/  mlx5_ib_destroy_wq ; 
 int /*<<< orphan*/  mlx5_ib_get_netdev ; 
 int /*<<< orphan*/  mlx5_ib_modify_wq ; 

__attribute__((used)) static int mlx5_ib_stage_common_roce_init(struct mlx5_ib_dev *dev)
{
	u8 port_num;
	int i;

	for (i = 0; i < dev->num_ports; i++) {
		dev->roce[i].dev = dev;
		dev->roce[i].native_port_num = i + 1;
		dev->roce[i].last_port_state = IB_PORT_DOWN;
	}

	dev->ib_dev.get_netdev	= mlx5_ib_get_netdev;
	dev->ib_dev.create_wq	 = mlx5_ib_create_wq;
	dev->ib_dev.modify_wq	 = mlx5_ib_modify_wq;
	dev->ib_dev.destroy_wq	 = mlx5_ib_destroy_wq;
	dev->ib_dev.create_rwq_ind_table = mlx5_ib_create_rwq_ind_table;
	dev->ib_dev.destroy_rwq_ind_table = mlx5_ib_destroy_rwq_ind_table;

	dev->ib_dev.uverbs_ex_cmd_mask |=
			(1ull << IB_USER_VERBS_EX_CMD_CREATE_WQ) |
			(1ull << IB_USER_VERBS_EX_CMD_MODIFY_WQ) |
			(1ull << IB_USER_VERBS_EX_CMD_DESTROY_WQ) |
			(1ull << IB_USER_VERBS_EX_CMD_CREATE_RWQ_IND_TBL) |
			(1ull << IB_USER_VERBS_EX_CMD_DESTROY_RWQ_IND_TBL);

	port_num = mlx5_core_native_port_num(dev->mdev) - 1;

	return mlx5_add_netdev_notifier(dev, port_num);
}