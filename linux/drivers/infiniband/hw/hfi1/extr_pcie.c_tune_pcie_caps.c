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
struct pci_dev {int pcie_mpss; TYPE_1__* bus; } ;
struct hfi1_devdata {struct pci_dev* pcidev; } ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_DEVCTL ; 
 int PCI_EXP_DEVCTL_EXT_TAG ; 
 int /*<<< orphan*/  dd_dev_info (struct hfi1_devdata*,char*) ; 
 int ffs (int /*<<< orphan*/ ) ; 
 int hfi1_pcie_caps ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_is_root_bus (TYPE_1__*) ; 
 int pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int pcie_capability_write_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcie_get_mps (struct pci_dev*) ; 
 int pcie_get_readrq (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_set_mps (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pcie_set_readrq (struct pci_dev*,int) ; 

void tune_pcie_caps(struct hfi1_devdata *dd)
{
	struct pci_dev *parent;
	u16 rc_mpss, rc_mps, ep_mpss, ep_mps;
	u16 rc_mrrs, ep_mrrs, max_mrrs, ectl;
	int ret;

	/*
	 * Turn on extended tags in DevCtl in case the BIOS has turned it off
	 * to improve WFR SDMA bandwidth
	 */
	ret = pcie_capability_read_word(dd->pcidev, PCI_EXP_DEVCTL, &ectl);
	if ((!ret) && !(ectl & PCI_EXP_DEVCTL_EXT_TAG)) {
		dd_dev_info(dd, "Enabling PCIe extended tags\n");
		ectl |= PCI_EXP_DEVCTL_EXT_TAG;
		ret = pcie_capability_write_word(dd->pcidev,
						 PCI_EXP_DEVCTL, ectl);
		if (ret)
			dd_dev_info(dd, "Unable to write to PCI config\n");
	}
	/* Find out supported and configured values for parent (root) */
	parent = dd->pcidev->bus->self;
	/*
	 * The driver cannot perform the tuning if it does not have
	 * access to the upstream component.
	 */
	if (!parent) {
		dd_dev_info(dd, "Parent not found\n");
		return;
	}
	if (!pci_is_root_bus(parent->bus)) {
		dd_dev_info(dd, "Parent not root\n");
		return;
	}
	if (!pci_is_pcie(parent)) {
		dd_dev_info(dd, "Parent is not PCI Express capable\n");
		return;
	}
	if (!pci_is_pcie(dd->pcidev)) {
		dd_dev_info(dd, "PCI device is not PCI Express capable\n");
		return;
	}
	rc_mpss = parent->pcie_mpss;
	rc_mps = ffs(pcie_get_mps(parent)) - 8;
	/* Find out supported and configured values for endpoint (us) */
	ep_mpss = dd->pcidev->pcie_mpss;
	ep_mps = ffs(pcie_get_mps(dd->pcidev)) - 8;

	/* Find max payload supported by root, endpoint */
	if (rc_mpss > ep_mpss)
		rc_mpss = ep_mpss;

	/* If Supported greater than limit in module param, limit it */
	if (rc_mpss > (hfi1_pcie_caps & 7))
		rc_mpss = hfi1_pcie_caps & 7;
	/* If less than (allowed, supported), bump root payload */
	if (rc_mpss > rc_mps) {
		rc_mps = rc_mpss;
		pcie_set_mps(parent, 128 << rc_mps);
	}
	/* If less than (allowed, supported), bump endpoint payload */
	if (rc_mpss > ep_mps) {
		ep_mps = rc_mpss;
		pcie_set_mps(dd->pcidev, 128 << ep_mps);
	}

	/*
	 * Now the Read Request size.
	 * No field for max supported, but PCIe spec limits it to 4096,
	 * which is code '5' (log2(4096) - 7)
	 */
	max_mrrs = 5;
	if (max_mrrs > ((hfi1_pcie_caps >> 4) & 7))
		max_mrrs = (hfi1_pcie_caps >> 4) & 7;

	max_mrrs = 128 << max_mrrs;
	rc_mrrs = pcie_get_readrq(parent);
	ep_mrrs = pcie_get_readrq(dd->pcidev);

	if (max_mrrs > rc_mrrs) {
		rc_mrrs = max_mrrs;
		pcie_set_readrq(parent, rc_mrrs);
	}
	if (max_mrrs > ep_mrrs) {
		ep_mrrs = max_mrrs;
		pcie_set_readrq(dd->pcidev, ep_mrrs);
	}
}