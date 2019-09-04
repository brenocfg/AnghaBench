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
struct mlx5_priv {int dummy; } ;
struct mlx5_core_dev {TYPE_1__* pdev; struct mlx5_priv priv; } ;
struct devlink {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devlink_free (struct devlink*) ; 
 int /*<<< orphan*/  devlink_unregister (struct devlink*) ; 
 int /*<<< orphan*/  mlx5_health_cleanup (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_pagealloc_cleanup (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_pci_close (struct mlx5_core_dev*,struct mlx5_priv*) ; 
 scalar_t__ mlx5_unload_one (struct mlx5_core_dev*,struct mlx5_priv*,int) ; 
 int /*<<< orphan*/  mlx5_unregister_device (struct mlx5_core_dev*) ; 
 struct mlx5_core_dev* pci_get_drvdata (struct pci_dev*) ; 
 struct devlink* priv_to_devlink (struct mlx5_core_dev*) ; 

__attribute__((used)) static void remove_one(struct pci_dev *pdev)
{
	struct mlx5_core_dev *dev  = pci_get_drvdata(pdev);
	struct devlink *devlink = priv_to_devlink(dev);
	struct mlx5_priv *priv = &dev->priv;

	devlink_unregister(devlink);
	mlx5_unregister_device(dev);

	if (mlx5_unload_one(dev, priv, true)) {
		dev_err(&dev->pdev->dev, "mlx5_unload_one failed\n");
		mlx5_health_cleanup(dev);
		return;
	}

	mlx5_pagealloc_cleanup(dev);
	mlx5_health_cleanup(dev);
	mlx5_pci_close(dev, priv);
#ifdef CONFIG_INFINIBAND_ON_DEMAND_PAGING
	cleanup_srcu_struct(&priv->pfault_srcu);
#endif
	devlink_free(devlink);
}