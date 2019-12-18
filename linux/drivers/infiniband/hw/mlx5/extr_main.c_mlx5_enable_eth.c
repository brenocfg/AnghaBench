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
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5_eth_lag_init (struct mlx5_ib_dev*) ; 
 int /*<<< orphan*/  mlx5_nic_vport_disable_roce (int /*<<< orphan*/ ) ; 
 int mlx5_nic_vport_enable_roce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce ; 

__attribute__((used)) static int mlx5_enable_eth(struct mlx5_ib_dev *dev)
{
	int err;

	if (MLX5_CAP_GEN(dev->mdev, roce)) {
		err = mlx5_nic_vport_enable_roce(dev->mdev);
		if (err)
			return err;
	}

	err = mlx5_eth_lag_init(dev);
	if (err)
		goto err_disable_roce;

	return 0;

err_disable_roce:
	if (MLX5_CAP_GEN(dev->mdev, roce))
		mlx5_nic_vport_disable_roce(dev->mdev);

	return err;
}