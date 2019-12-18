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
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {struct e1000_hw hw; struct pci_dev* pdev; } ;

/* Variables and functions */
 scalar_t__ e1000_i210 ; 
 scalar_t__ e1000_i211 ; 
 int /*<<< orphan*/  igb_enable_sriov (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igb_reset_interrupt_capability (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_set_interrupt_capability (struct igb_adapter*,int) ; 
 int /*<<< orphan*/  max_vfs ; 
 int /*<<< orphan*/  pci_sriov_set_totalvfs (struct pci_dev*,int) ; 

__attribute__((used)) static void igb_probe_vfs(struct igb_adapter *adapter)
{
#ifdef CONFIG_PCI_IOV
	struct pci_dev *pdev = adapter->pdev;
	struct e1000_hw *hw = &adapter->hw;

	/* Virtualization features not supported on i210 family. */
	if ((hw->mac.type == e1000_i210) || (hw->mac.type == e1000_i211))
		return;

	/* Of the below we really only want the effect of getting
	 * IGB_FLAG_HAS_MSIX set (if available), without which
	 * igb_enable_sriov() has no effect.
	 */
	igb_set_interrupt_capability(adapter, true);
	igb_reset_interrupt_capability(adapter);

	pci_sriov_set_totalvfs(pdev, 7);
	igb_enable_sriov(pdev, max_vfs);

#endif /* CONFIG_PCI_IOV */
}