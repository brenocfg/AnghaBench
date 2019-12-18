#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int MLX5_CAP_ESW_FLOWTABLE_FDB (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int MLX5_CAP_FLOWTABLE_NIC_RX (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int MLX5_FLOW_NAMESPACE_FDB ; 
 int /*<<< orphan*/  max_modify_header_actions ; 

__attribute__((used)) static int mlx5e_flow_namespace_max_modify_action(struct mlx5_core_dev *mdev,
						  int namespace)
{
	if (namespace == MLX5_FLOW_NAMESPACE_FDB) /* FDB offloading */
		return MLX5_CAP_ESW_FLOWTABLE_FDB(mdev, max_modify_header_actions);
	else /* namespace is MLX5_FLOW_NAMESPACE_KERNEL - NIC offloading */
		return MLX5_CAP_FLOWTABLE_NIC_RX(mdev, max_modify_header_actions);
}