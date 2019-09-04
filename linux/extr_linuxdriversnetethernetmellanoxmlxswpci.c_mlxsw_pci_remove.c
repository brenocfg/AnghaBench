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
struct mlxsw_pci {int /*<<< orphan*/  pdev; int /*<<< orphan*/  hw_addr; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_pci*) ; 
 int /*<<< orphan*/  mlxsw_core_bus_device_unregister (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 struct mlxsw_pci* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_pci_remove(struct pci_dev *pdev)
{
	struct mlxsw_pci *mlxsw_pci = pci_get_drvdata(pdev);

	mlxsw_core_bus_device_unregister(mlxsw_pci->core, false);
	iounmap(mlxsw_pci->hw_addr);
	pci_release_regions(mlxsw_pci->pdev);
	pci_disable_device(mlxsw_pci->pdev);
	kfree(mlxsw_pci);
}