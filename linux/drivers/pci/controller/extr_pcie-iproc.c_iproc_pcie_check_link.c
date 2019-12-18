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
typedef  int u32 ;
struct iproc_pcie {scalar_t__ ep_is_internal; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENODEV ; 
 int /*<<< orphan*/  IPROC_PCIE_LINK_STATUS ; 
 scalar_t__ IPROC_PCI_EXP_CAP ; 
 int PCIE_DL_ACTIVE ; 
 int PCIE_PHYLINKUP ; 
 scalar_t__ PCI_BRIDGE_CTRL_REG_OFFSET ; 
 int PCI_CLASS_BRIDGE_MASK ; 
 int PCI_CLASS_BRIDGE_PCI ; 
 int PCI_CLASS_BRIDGE_SHIFT ; 
 scalar_t__ PCI_EXP_LNKCTL2 ; 
 scalar_t__ PCI_EXP_LNKSTA ; 
 int PCI_EXP_LNKSTA_NLW ; 
 scalar_t__ PCI_HEADER_TYPE ; 
 int PCI_HEADER_TYPE_BRIDGE ; 
 int PCI_TARGET_LINK_SPEED_GEN1 ; 
 int PCI_TARGET_LINK_SPEED_GEN2 ; 
 int PCI_TARGET_LINK_SPEED_MASK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char*) ; 
 int /*<<< orphan*/  iproc_pci_raw_config_read32 (struct iproc_pcie*,int /*<<< orphan*/ ,scalar_t__,int,int*) ; 
 int /*<<< orphan*/  iproc_pci_raw_config_write32 (struct iproc_pcie*,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int iproc_pcie_read_reg (struct iproc_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int iproc_pcie_check_link(struct iproc_pcie *pcie)
{
	struct device *dev = pcie->dev;
	u32 hdr_type, link_ctrl, link_status, class, val;
	bool link_is_active = false;

	/*
	 * PAXC connects to emulated endpoint devices directly and does not
	 * have a Serdes.  Therefore skip the link detection logic here.
	 */
	if (pcie->ep_is_internal)
		return 0;

	val = iproc_pcie_read_reg(pcie, IPROC_PCIE_LINK_STATUS);
	if (!(val & PCIE_PHYLINKUP) || !(val & PCIE_DL_ACTIVE)) {
		dev_err(dev, "PHY or data link is INACTIVE!\n");
		return -ENODEV;
	}

	/* make sure we are not in EP mode */
	iproc_pci_raw_config_read32(pcie, 0, PCI_HEADER_TYPE, 1, &hdr_type);
	if ((hdr_type & 0x7f) != PCI_HEADER_TYPE_BRIDGE) {
		dev_err(dev, "in EP mode, hdr=%#02x\n", hdr_type);
		return -EFAULT;
	}

	/* force class to PCI_CLASS_BRIDGE_PCI (0x0604) */
#define PCI_BRIDGE_CTRL_REG_OFFSET	0x43c
#define PCI_CLASS_BRIDGE_MASK		0xffff00
#define PCI_CLASS_BRIDGE_SHIFT		8
	iproc_pci_raw_config_read32(pcie, 0, PCI_BRIDGE_CTRL_REG_OFFSET,
				    4, &class);
	class &= ~PCI_CLASS_BRIDGE_MASK;
	class |= (PCI_CLASS_BRIDGE_PCI << PCI_CLASS_BRIDGE_SHIFT);
	iproc_pci_raw_config_write32(pcie, 0, PCI_BRIDGE_CTRL_REG_OFFSET,
				     4, class);

	/* check link status to see if link is active */
	iproc_pci_raw_config_read32(pcie, 0, IPROC_PCI_EXP_CAP + PCI_EXP_LNKSTA,
				    2, &link_status);
	if (link_status & PCI_EXP_LNKSTA_NLW)
		link_is_active = true;

	if (!link_is_active) {
		/* try GEN 1 link speed */
#define PCI_TARGET_LINK_SPEED_MASK	0xf
#define PCI_TARGET_LINK_SPEED_GEN2	0x2
#define PCI_TARGET_LINK_SPEED_GEN1	0x1
		iproc_pci_raw_config_read32(pcie, 0,
					    IPROC_PCI_EXP_CAP + PCI_EXP_LNKCTL2,
					    4, &link_ctrl);
		if ((link_ctrl & PCI_TARGET_LINK_SPEED_MASK) ==
		    PCI_TARGET_LINK_SPEED_GEN2) {
			link_ctrl &= ~PCI_TARGET_LINK_SPEED_MASK;
			link_ctrl |= PCI_TARGET_LINK_SPEED_GEN1;
			iproc_pci_raw_config_write32(pcie, 0,
					IPROC_PCI_EXP_CAP + PCI_EXP_LNKCTL2,
					4, link_ctrl);
			msleep(100);

			iproc_pci_raw_config_read32(pcie, 0,
					IPROC_PCI_EXP_CAP + PCI_EXP_LNKSTA,
					2, &link_status);
			if (link_status & PCI_EXP_LNKSTA_NLW)
				link_is_active = true;
		}
	}

	dev_info(dev, "link: %s\n", link_is_active ? "UP" : "DOWN");

	return link_is_active ? 0 : -ENODEV;
}