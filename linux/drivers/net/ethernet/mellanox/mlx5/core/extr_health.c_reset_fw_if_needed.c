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
typedef  scalar_t__ u32 ;
struct mlx5_core_dev {TYPE_1__* iseg; } ;
struct TYPE_2__ {int /*<<< orphan*/  initializing; } ;

/* Variables and functions */
 int MLX5_FW_RESET_SUPPORTED_OFFSET ; 
 int /*<<< orphan*/  MLX5_NIC_IFC_SW_RESET ; 
 scalar_t__ MLX5_SENSOR_NIC_DISABLED ; 
 scalar_t__ MLX5_SENSOR_NIC_SW_RESET ; 
 scalar_t__ MLX5_SENSOR_PCI_COMM_ERR ; 
 scalar_t__ check_fatal_sensors (struct mlx5_core_dev*) ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  mlx5_set_nic_state (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool reset_fw_if_needed(struct mlx5_core_dev *dev)
{
	bool supported = (ioread32be(&dev->iseg->initializing) >>
			  MLX5_FW_RESET_SUPPORTED_OFFSET) & 1;
	u32 fatal_error;

	if (!supported)
		return false;

	/* The reset only needs to be issued by one PF. The health buffer is
	 * shared between all functions, and will be cleared during a reset.
	 * Check again to avoid a redundant 2nd reset. If the fatal erros was
	 * PCI related a reset won't help.
	 */
	fatal_error = check_fatal_sensors(dev);
	if (fatal_error == MLX5_SENSOR_PCI_COMM_ERR ||
	    fatal_error == MLX5_SENSOR_NIC_DISABLED ||
	    fatal_error == MLX5_SENSOR_NIC_SW_RESET) {
		mlx5_core_warn(dev, "Not issuing FW reset. Either it's already done or won't help.");
		return false;
	}

	mlx5_core_warn(dev, "Issuing FW Reset\n");
	/* Write the NIC interface field to initiate the reset, the command
	 * interface address also resides here, don't overwrite it.
	 */
	mlx5_set_nic_state(dev, MLX5_NIC_IFC_SW_RESET);

	return true;
}