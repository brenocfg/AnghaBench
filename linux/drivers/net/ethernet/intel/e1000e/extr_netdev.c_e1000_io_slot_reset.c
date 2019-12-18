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
typedef  int u16 ;
struct pci_dev {int state_saved; int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct e1000_hw {int dummy; } ;
struct e1000_adapter {int flags2; struct e1000_hw hw; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;

/* Variables and functions */
 int FLAG2_DISABLE_ASPM_L0S ; 
 int FLAG2_DISABLE_ASPM_L1 ; 
 int PCIE_LINK_STATE_L0S ; 
 int PCIE_LINK_STATE_L1 ; 
 int /*<<< orphan*/  PCI_D3cold ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 int /*<<< orphan*/  WUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  e1000e_disable_aspm_locked (struct pci_dev*,int) ; 
 int /*<<< orphan*/  e1000e_reset (struct e1000_adapter*) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int pci_enable_device_mem (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_wake (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 

__attribute__((used)) static pci_ers_result_t e1000_io_slot_reset(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	u16 aspm_disable_flag = 0;
	int err;
	pci_ers_result_t result;

	if (adapter->flags2 & FLAG2_DISABLE_ASPM_L0S)
		aspm_disable_flag = PCIE_LINK_STATE_L0S;
	if (adapter->flags2 & FLAG2_DISABLE_ASPM_L1)
		aspm_disable_flag |= PCIE_LINK_STATE_L1;
	if (aspm_disable_flag)
		e1000e_disable_aspm_locked(pdev, aspm_disable_flag);

	err = pci_enable_device_mem(pdev);
	if (err) {
		dev_err(&pdev->dev,
			"Cannot re-enable PCI device after reset.\n");
		result = PCI_ERS_RESULT_DISCONNECT;
	} else {
		pdev->state_saved = true;
		pci_restore_state(pdev);
		pci_set_master(pdev);

		pci_enable_wake(pdev, PCI_D3hot, 0);
		pci_enable_wake(pdev, PCI_D3cold, 0);

		e1000e_reset(adapter);
		ew32(WUS, ~0);
		result = PCI_ERS_RESULT_RECOVERED;
	}

	return result;
}