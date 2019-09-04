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
typedef  int u8 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
#define  MLX5_NIC_IFC_DISABLED 130 
#define  MLX5_NIC_IFC_FULL 129 
#define  MLX5_NIC_IFC_NO_DRAM_NIC 128 
 int get_nic_state (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,...) ; 
 int /*<<< orphan*/  mlx5_disable_device (struct mlx5_core_dev*) ; 

__attribute__((used)) static void mlx5_handle_bad_state(struct mlx5_core_dev *dev)
{
	u8 nic_interface = get_nic_state(dev);

	switch (nic_interface) {
	case MLX5_NIC_IFC_FULL:
		mlx5_core_warn(dev, "Expected to see disabled NIC but it is full driver\n");
		break;

	case MLX5_NIC_IFC_DISABLED:
		mlx5_core_warn(dev, "starting teardown\n");
		break;

	case MLX5_NIC_IFC_NO_DRAM_NIC:
		mlx5_core_warn(dev, "Expected to see disabled NIC but it is no dram nic\n");
		break;
	default:
		mlx5_core_warn(dev, "Expected to see disabled NIC but it is has invalid value %d\n",
			       nic_interface);
	}

	mlx5_disable_device(dev);
}