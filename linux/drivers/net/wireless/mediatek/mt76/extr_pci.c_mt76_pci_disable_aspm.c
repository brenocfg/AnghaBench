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
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  dev; TYPE_1__* bus; } ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PCIEASPM ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_EXP_LNKCTL ; 
 int PCI_EXP_LNKCTL_ASPMC ; 
 int PCI_EXP_LNKCTL_ASPM_L0S ; 
 int PCI_EXP_LNKCTL_ASPM_L1 ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int pci_disable_link_state (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pcie_capability_clear_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

void mt76_pci_disable_aspm(struct pci_dev *pdev)
{
	struct pci_dev *parent = pdev->bus->self;
	u16 aspm_conf, parent_aspm_conf = 0;

	pcie_capability_read_word(pdev, PCI_EXP_LNKCTL, &aspm_conf);
	aspm_conf &= PCI_EXP_LNKCTL_ASPMC;
	if (parent) {
		pcie_capability_read_word(parent, PCI_EXP_LNKCTL,
					  &parent_aspm_conf);
		parent_aspm_conf &= PCI_EXP_LNKCTL_ASPMC;
	}

	if (!aspm_conf && (!parent || !parent_aspm_conf)) {
		/* aspm already disabled */
		return;
	}

	dev_info(&pdev->dev, "disabling ASPM %s %s\n",
		 (aspm_conf & PCI_EXP_LNKCTL_ASPM_L0S) ? "L0s" : "",
		 (aspm_conf & PCI_EXP_LNKCTL_ASPM_L1) ? "L1" : "");

	if (IS_ENABLED(CONFIG_PCIEASPM)) {
		int err;

		err = pci_disable_link_state(pdev, aspm_conf);
		if (!err)
			return;
	}

	/* both device and parent should have the same ASPM setting.
	 * disable ASPM in downstream component first and then upstream.
	 */
	pcie_capability_clear_word(pdev, PCI_EXP_LNKCTL, aspm_conf);
	if (parent)
		pcie_capability_clear_word(parent, PCI_EXP_LNKCTL,
					   aspm_conf);
}