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
struct pci_dev {int dummy; } ;
struct mlx5_core_sriov {scalar_t__ num_vfs; } ;
struct TYPE_2__ {struct mlx5_core_sriov sriov; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_device_disable_sriov (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_pci_disable_sriov (struct pci_dev*) ; 
 struct mlx5_core_dev* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void mlx5_sriov_disable(struct pci_dev *pdev)
{
	struct mlx5_core_dev *dev  = pci_get_drvdata(pdev);
	struct mlx5_core_sriov *sriov = &dev->priv.sriov;

	mlx5_pci_disable_sriov(pdev);
	mlx5_device_disable_sriov(dev);
	sriov->num_vfs = 0;
}