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
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  mlx5_nic_vport_disable_roce (struct mlx5_core_dev*) ; 
 int mlx5_nic_vport_enable_roce (struct mlx5_core_dev*) ; 
 int mlx5_rdma_add_roce_addr (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_rdma_del_roce_addr (struct mlx5_core_dev*) ; 
 int mlx5_rdma_enable_roce_steering (struct mlx5_core_dev*) ; 

void mlx5_rdma_enable_roce(struct mlx5_core_dev *dev)
{
	int err;

	err = mlx5_nic_vport_enable_roce(dev);
	if (err) {
		mlx5_core_err(dev, "Failed to enable RoCE: %d\n", err);
		return;
	}

	err = mlx5_rdma_add_roce_addr(dev);
	if (err) {
		mlx5_core_err(dev, "Failed to add RoCE address: %d\n", err);
		goto disable_roce;
	}

	err = mlx5_rdma_enable_roce_steering(dev);
	if (err) {
		mlx5_core_err(dev, "Failed to enable RoCE steering: %d\n", err);
		goto del_roce_addr;
	}

	return;

del_roce_addr:
	mlx5_rdma_del_roce_addr(dev);
disable_roce:
	mlx5_nic_vport_disable_roce(dev);
	return;
}