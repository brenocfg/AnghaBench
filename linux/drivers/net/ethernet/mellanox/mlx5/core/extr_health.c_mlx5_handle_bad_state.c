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
typedef  int u8 ;
struct TYPE_3__ {int /*<<< orphan*/  fatal_error; } ;
struct TYPE_4__ {TYPE_1__ health; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;

/* Variables and functions */
#define  MLX5_NIC_IFC_DISABLED 131 
#define  MLX5_NIC_IFC_FULL 130 
#define  MLX5_NIC_IFC_NO_DRAM_NIC 129 
#define  MLX5_NIC_IFC_SW_RESET 128 
 int /*<<< orphan*/  MLX5_SENSOR_PCI_COMM_ERR ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,...) ; 
 int /*<<< orphan*/  mlx5_disable_device (struct mlx5_core_dev*) ; 
 int mlx5_get_nic_state (struct mlx5_core_dev*) ; 

__attribute__((used)) static void mlx5_handle_bad_state(struct mlx5_core_dev *dev)
{
	u8 nic_interface = mlx5_get_nic_state(dev);

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

	case MLX5_NIC_IFC_SW_RESET:
		/* The IFC mode field is 3 bits, so it will read 0x7 in 2 cases:
		 * 1. PCI has been disabled (ie. PCI-AER, PF driver unloaded
		 *    and this is a VF), this is not recoverable by SW reset.
		 *    Logging of this is handled elsewhere.
		 * 2. FW reset has been issued by another function, driver can
		 *    be reloaded to recover after the mode switches to
		 *    MLX5_NIC_IFC_DISABLED.
		 */
		if (dev->priv.health.fatal_error != MLX5_SENSOR_PCI_COMM_ERR)
			mlx5_core_warn(dev, "NIC SW reset in progress\n");
		break;

	default:
		mlx5_core_warn(dev, "Expected to see disabled NIC but it is has invalid value %d\n",
			       nic_interface);
	}

	mlx5_disable_device(dev);
}