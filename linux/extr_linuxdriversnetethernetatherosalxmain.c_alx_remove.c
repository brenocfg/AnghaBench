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
struct alx_hw {int /*<<< orphan*/  hw_addr; int /*<<< orphan*/  perm_addr; } ;
struct alx_priv {int /*<<< orphan*/  dev; int /*<<< orphan*/  reset_wk; int /*<<< orphan*/  link_check_wk; struct alx_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  alx_set_macaddr (struct alx_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 struct alx_priv* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_mem_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alx_remove(struct pci_dev *pdev)
{
	struct alx_priv *alx = pci_get_drvdata(pdev);
	struct alx_hw *hw = &alx->hw;

	cancel_work_sync(&alx->link_check_wk);
	cancel_work_sync(&alx->reset_wk);

	/* restore permanent mac address */
	alx_set_macaddr(hw, hw->perm_addr);

	unregister_netdev(alx->dev);
	iounmap(hw->hw_addr);
	pci_release_mem_regions(pdev);

	pci_disable_pcie_error_reporting(pdev);
	pci_disable_device(pdev);

	free_netdev(alx->dev);
}