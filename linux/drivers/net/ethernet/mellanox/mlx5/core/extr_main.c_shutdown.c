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
 int /*<<< orphan*/  mlx5_core_info (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  mlx5_pci_disable_device (struct mlx5_core_dev*) ; 
 int mlx5_try_fast_unload (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_unload_one (struct mlx5_core_dev*,int) ; 
 struct mlx5_core_dev* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void shutdown(struct pci_dev *pdev)
{
	struct mlx5_core_dev *dev  = pci_get_drvdata(pdev);
	int err;

	mlx5_core_info(dev, "Shutdown was called\n");
	err = mlx5_try_fast_unload(dev);
	if (err)
		mlx5_unload_one(dev, false);
	mlx5_pci_disable_device(dev);
}