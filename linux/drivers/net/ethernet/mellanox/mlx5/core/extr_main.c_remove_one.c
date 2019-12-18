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
struct devlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  mlx5_crdump_disable (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_devlink_free (struct devlink*) ; 
 int /*<<< orphan*/  mlx5_devlink_unregister (struct devlink*) ; 
 int /*<<< orphan*/  mlx5_health_flush (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_mdev_uninit (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_pci_close (struct mlx5_core_dev*) ; 
 scalar_t__ mlx5_unload_one (struct mlx5_core_dev*,int) ; 
 struct mlx5_core_dev* pci_get_drvdata (struct pci_dev*) ; 
 struct devlink* priv_to_devlink (struct mlx5_core_dev*) ; 

__attribute__((used)) static void remove_one(struct pci_dev *pdev)
{
	struct mlx5_core_dev *dev  = pci_get_drvdata(pdev);
	struct devlink *devlink = priv_to_devlink(dev);

	mlx5_crdump_disable(dev);
	mlx5_devlink_unregister(devlink);

	if (mlx5_unload_one(dev, true)) {
		mlx5_core_err(dev, "mlx5_unload_one failed\n");
		mlx5_health_flush(dev);
		return;
	}

	mlx5_pci_close(dev);
	mlx5_mdev_uninit(dev);
	mlx5_devlink_free(devlink);
}