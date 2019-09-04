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
typedef  int /*<<< orphan*/  u16 ;
struct mlx5e_params {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_SW2HW_MTU (struct mlx5e_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_modify_nic_vport_mtu (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int mlx5_set_port_mtu (struct mlx5_core_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mlx5e_set_mtu(struct mlx5_core_dev *mdev,
			 struct mlx5e_params *params, u16 mtu)
{
	u16 hw_mtu = MLX5E_SW2HW_MTU(params, mtu);
	int err;

	err = mlx5_set_port_mtu(mdev, hw_mtu, 1);
	if (err)
		return err;

	/* Update vport context MTU */
	mlx5_modify_nic_vport_mtu(mdev, hw_mtu);
	return 0;
}