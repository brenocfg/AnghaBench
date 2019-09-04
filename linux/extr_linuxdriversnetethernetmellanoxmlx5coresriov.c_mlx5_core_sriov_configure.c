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
struct pci_dev {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPERM ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  mlx5_core_is_pf (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_lag_allow (struct mlx5_core_dev*) ; 
 int mlx5_lag_forbid (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_sriov_disable (struct pci_dev*) ; 
 int mlx5_sriov_enable (struct pci_dev*,int) ; 
 struct mlx5_core_dev* pci_get_drvdata (struct pci_dev*) ; 

int mlx5_core_sriov_configure(struct pci_dev *pdev, int num_vfs)
{
	struct mlx5_core_dev *dev  = pci_get_drvdata(pdev);
	int err = 0;

	mlx5_core_dbg(dev, "requested num_vfs %d\n", num_vfs);
	if (!mlx5_core_is_pf(dev))
		return -EPERM;

	if (num_vfs) {
		int ret;

		ret = mlx5_lag_forbid(dev);
		if (ret && (ret != -ENODEV))
			return ret;
	}

	if (num_vfs) {
		err = mlx5_sriov_enable(pdev, num_vfs);
	} else {
		mlx5_sriov_disable(pdev);
		mlx5_lag_allow(dev);
	}

	return err ? err : num_vfs;
}