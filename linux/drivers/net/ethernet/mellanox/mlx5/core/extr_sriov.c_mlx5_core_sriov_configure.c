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
struct mlx5_core_sriov {int num_vfs; } ;
struct TYPE_2__ {struct mlx5_core_sriov sriov; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  mlx5_sriov_disable (struct pci_dev*) ; 
 int mlx5_sriov_enable (struct pci_dev*,int) ; 
 struct mlx5_core_dev* pci_get_drvdata (struct pci_dev*) ; 

int mlx5_core_sriov_configure(struct pci_dev *pdev, int num_vfs)
{
	struct mlx5_core_dev *dev  = pci_get_drvdata(pdev);
	struct mlx5_core_sriov *sriov = &dev->priv.sriov;
	int err = 0;

	mlx5_core_dbg(dev, "requested num_vfs %d\n", num_vfs);

	if (num_vfs)
		err = mlx5_sriov_enable(pdev, num_vfs);
	else
		mlx5_sriov_disable(pdev);

	if (!err)
		sriov->num_vfs = num_vfs;
	return err ? err : num_vfs;
}