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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct alx_hw {int dummy; } ;
struct alx_priv {struct alx_hw hw; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 int /*<<< orphan*/  alx_reset_mac (struct alx_hw*) ; 
 int /*<<< orphan*/  alx_reset_pcie (struct alx_hw*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 struct alx_priv* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static pci_ers_result_t alx_pci_error_slot_reset(struct pci_dev *pdev)
{
	struct alx_priv *alx = pci_get_drvdata(pdev);
	struct alx_hw *hw = &alx->hw;
	pci_ers_result_t rc = PCI_ERS_RESULT_DISCONNECT;

	dev_info(&pdev->dev, "pci error slot reset\n");

	rtnl_lock();

	if (pci_enable_device(pdev)) {
		dev_err(&pdev->dev, "Failed to re-enable PCI device after reset\n");
		goto out;
	}

	pci_set_master(pdev);

	alx_reset_pcie(hw);
	if (!alx_reset_mac(hw))
		rc = PCI_ERS_RESULT_RECOVERED;
out:
	rtnl_unlock();

	return rc;
}