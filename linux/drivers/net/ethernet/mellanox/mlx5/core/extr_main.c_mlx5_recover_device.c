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
struct mlx5_core_dev {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ PCI_ERS_RESULT_RECOVERED ; 
 int /*<<< orphan*/  mlx5_pci_disable_device (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_pci_resume (int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5_pci_slot_reset (int /*<<< orphan*/ ) ; 

void mlx5_recover_device(struct mlx5_core_dev *dev)
{
	mlx5_pci_disable_device(dev);
	if (mlx5_pci_slot_reset(dev->pdev) == PCI_ERS_RESULT_RECOVERED)
		mlx5_pci_resume(dev->pdev);
}