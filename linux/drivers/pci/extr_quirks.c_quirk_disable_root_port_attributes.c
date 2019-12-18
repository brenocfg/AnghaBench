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

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_DEVCTL ; 
 int PCI_EXP_DEVCTL_NOSNOOP_EN ; 
 int PCI_EXP_DEVCTL_RELAX_EN ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct pci_dev* pci_find_pcie_root_port (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_warn (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pcie_capability_clear_and_set_word (struct pci_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void quirk_disable_root_port_attributes(struct pci_dev *pdev)
{
	struct pci_dev *root_port = pci_find_pcie_root_port(pdev);

	if (!root_port) {
		pci_warn(pdev, "PCIe Completion erratum may cause device errors\n");
		return;
	}

	pci_info(root_port, "Disabling No Snoop/Relaxed Ordering Attributes to avoid PCIe Completion erratum in %s\n",
		 dev_name(&pdev->dev));
	pcie_capability_clear_and_set_word(root_port, PCI_EXP_DEVCTL,
					   PCI_EXP_DEVCTL_RELAX_EN |
					   PCI_EXP_DEVCTL_NOSNOOP_EN, 0);
}