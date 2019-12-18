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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int /*<<< orphan*/  multifunction; } ;

/* Variables and functions */
#define  PCI_EXP_TYPE_DOWNSTREAM 136 
#define  PCI_EXP_TYPE_ENDPOINT 135 
#define  PCI_EXP_TYPE_LEG_END 134 
#define  PCI_EXP_TYPE_PCIE_BRIDGE 133 
#define  PCI_EXP_TYPE_PCI_BRIDGE 132 
#define  PCI_EXP_TYPE_RC_EC 131 
#define  PCI_EXP_TYPE_RC_END 130 
#define  PCI_EXP_TYPE_ROOT_PORT 129 
#define  PCI_EXP_TYPE_UPSTREAM 128 
 int pci_acs_flags_enabled (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_dev_specific_acs_enabled (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 int pci_pcie_type (struct pci_dev*) ; 

bool pci_acs_enabled(struct pci_dev *pdev, u16 acs_flags)
{
	int ret;

	ret = pci_dev_specific_acs_enabled(pdev, acs_flags);
	if (ret >= 0)
		return ret > 0;

	/*
	 * Conventional PCI and PCI-X devices never support ACS, either
	 * effectively or actually.  The shared bus topology implies that
	 * any device on the bus can receive or snoop DMA.
	 */
	if (!pci_is_pcie(pdev))
		return false;

	switch (pci_pcie_type(pdev)) {
	/*
	 * PCI/X-to-PCIe bridges are not specifically mentioned by the spec,
	 * but since their primary interface is PCI/X, we conservatively
	 * handle them as we would a non-PCIe device.
	 */
	case PCI_EXP_TYPE_PCIE_BRIDGE:
	/*
	 * PCIe 3.0, 6.12.1 excludes ACS on these devices.  "ACS is never
	 * applicable... must never implement an ACS Extended Capability...".
	 * This seems arbitrary, but we take a conservative interpretation
	 * of this statement.
	 */
	case PCI_EXP_TYPE_PCI_BRIDGE:
	case PCI_EXP_TYPE_RC_EC:
		return false;
	/*
	 * PCIe 3.0, 6.12.1.1 specifies that downstream and root ports should
	 * implement ACS in order to indicate their peer-to-peer capabilities,
	 * regardless of whether they are single- or multi-function devices.
	 */
	case PCI_EXP_TYPE_DOWNSTREAM:
	case PCI_EXP_TYPE_ROOT_PORT:
		return pci_acs_flags_enabled(pdev, acs_flags);
	/*
	 * PCIe 3.0, 6.12.1.2 specifies ACS capabilities that should be
	 * implemented by the remaining PCIe types to indicate peer-to-peer
	 * capabilities, but only when they are part of a multifunction
	 * device.  The footnote for section 6.12 indicates the specific
	 * PCIe types included here.
	 */
	case PCI_EXP_TYPE_ENDPOINT:
	case PCI_EXP_TYPE_UPSTREAM:
	case PCI_EXP_TYPE_LEG_END:
	case PCI_EXP_TYPE_RC_END:
		if (!pdev->multifunction)
			break;

		return pci_acs_flags_enabled(pdev, acs_flags);
	}

	/*
	 * PCIe 3.0, 6.12.1.3 specifies no ACS capabilities are applicable
	 * to single function devices with the exception of downstream ports.
	 */
	return true;
}