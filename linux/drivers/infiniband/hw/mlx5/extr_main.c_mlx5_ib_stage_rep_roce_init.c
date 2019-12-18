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
struct mlx5_ib_dev {struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  enum rdma_link_layer { ____Placeholder_rdma_link_layer } rdma_link_layer ;

/* Variables and functions */
 int IB_LINK_LAYER_ETHERNET ; 
 int MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int mlx5_ib_stage_common_roce_init (struct mlx5_ib_dev*) ; 
 int mlx5_port_type_cap_to_rdma_ll (int) ; 
 int /*<<< orphan*/  port_type ; 

__attribute__((used)) static int mlx5_ib_stage_rep_roce_init(struct mlx5_ib_dev *dev)
{
	struct mlx5_core_dev *mdev = dev->mdev;
	enum rdma_link_layer ll;
	int port_type_cap;
	int err = 0;

	port_type_cap = MLX5_CAP_GEN(mdev, port_type);
	ll = mlx5_port_type_cap_to_rdma_ll(port_type_cap);

	if (ll == IB_LINK_LAYER_ETHERNET)
		err = mlx5_ib_stage_common_roce_init(dev);

	return err;
}