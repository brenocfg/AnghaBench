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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_core_dev {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ MLX5_NIC_IFC_DISABLED ; 
 scalar_t__ MLX5_NIC_IFC_SW_RESET ; 
 int /*<<< orphan*/  MLX5_SENSOR_FW_SYND_RFR ; 
 int /*<<< orphan*/  MLX5_SENSOR_NIC_DISABLED ; 
 int /*<<< orphan*/  MLX5_SENSOR_NIC_SW_RESET ; 
 int /*<<< orphan*/  MLX5_SENSOR_NO_ERR ; 
 int /*<<< orphan*/  MLX5_SENSOR_PCI_COMM_ERR ; 
 int /*<<< orphan*/  MLX5_SENSOR_PCI_ERR ; 
 scalar_t__ mlx5_get_nic_state (struct mlx5_core_dev*) ; 
 scalar_t__ pci_channel_offline (int /*<<< orphan*/ ) ; 
 scalar_t__ sensor_fw_synd_rfr (struct mlx5_core_dev*) ; 
 scalar_t__ sensor_pci_not_working (struct mlx5_core_dev*) ; 

__attribute__((used)) static u32 check_fatal_sensors(struct mlx5_core_dev *dev)
{
	if (sensor_pci_not_working(dev))
		return MLX5_SENSOR_PCI_COMM_ERR;
	if (pci_channel_offline(dev->pdev))
		return MLX5_SENSOR_PCI_ERR;
	if (mlx5_get_nic_state(dev) == MLX5_NIC_IFC_DISABLED)
		return MLX5_SENSOR_NIC_DISABLED;
	if (mlx5_get_nic_state(dev) == MLX5_NIC_IFC_SW_RESET)
		return MLX5_SENSOR_NIC_SW_RESET;
	if (sensor_fw_synd_rfr(dev))
		return MLX5_SENSOR_FW_SYND_RFR;

	return MLX5_SENSOR_NO_ERR;
}