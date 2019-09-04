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
struct be_adapter {int /*<<< orphan*/  netdev; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  be_cancel_err_detection (struct be_adapter*) ; 
 int /*<<< orphan*/  be_clear (struct be_adapter*) ; 
 int /*<<< orphan*/  be_cmd_fw_clean (struct be_adapter*) ; 
 int /*<<< orphan*/  be_cmd_reset_function (struct be_adapter*) ; 
 int /*<<< orphan*/  be_drv_cleanup (struct be_adapter*) ; 
 int /*<<< orphan*/  be_intr_set (struct be_adapter*,int) ; 
 int /*<<< orphan*/  be_roce_dev_remove (struct be_adapter*) ; 
 int /*<<< orphan*/  be_unmap_pci_bars (struct be_adapter*) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 struct be_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_vfs_assigned (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void be_remove(struct pci_dev *pdev)
{
	struct be_adapter *adapter = pci_get_drvdata(pdev);

	if (!adapter)
		return;

	be_roce_dev_remove(adapter);
	be_intr_set(adapter, false);

	be_cancel_err_detection(adapter);

	unregister_netdev(adapter->netdev);

	be_clear(adapter);

	if (!pci_vfs_assigned(adapter->pdev))
		be_cmd_reset_function(adapter);

	/* tell fw we're done with firing cmds */
	be_cmd_fw_clean(adapter);

	be_unmap_pci_bars(adapter);
	be_drv_cleanup(adapter);

	pci_disable_pcie_error_reporting(pdev);

	pci_release_regions(pdev);
	pci_disable_device(pdev);

	free_netdev(adapter->netdev);
}