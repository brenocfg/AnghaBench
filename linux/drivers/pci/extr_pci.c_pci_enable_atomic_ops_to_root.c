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
struct pci_dev {struct pci_bus* bus; } ;
struct pci_bus {struct pci_bus* parent; struct pci_dev* self; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCI_EXP_DEVCAP2 ; 
 int PCI_EXP_DEVCAP2_ATOMIC_ROUTE ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL2 ; 
 int PCI_EXP_DEVCTL2_ATOMIC_EGRESS_BLOCK ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL2_ATOMIC_REQ ; 
#define  PCI_EXP_TYPE_DOWNSTREAM 133 
#define  PCI_EXP_TYPE_ENDPOINT 132 
#define  PCI_EXP_TYPE_LEG_END 131 
#define  PCI_EXP_TYPE_RC_END 130 
#define  PCI_EXP_TYPE_ROOT_PORT 129 
#define  PCI_EXP_TYPE_UPSTREAM 128 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 int const pci_pcie_type (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_capability_read_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pcie_capability_set_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pci_enable_atomic_ops_to_root(struct pci_dev *dev, u32 cap_mask)
{
	struct pci_bus *bus = dev->bus;
	struct pci_dev *bridge;
	u32 cap, ctl2;

	if (!pci_is_pcie(dev))
		return -EINVAL;

	/*
	 * Per PCIe r4.0, sec 6.15, endpoints and root ports may be
	 * AtomicOp requesters.  For now, we only support endpoints as
	 * requesters and root ports as completers.  No endpoints as
	 * completers, and no peer-to-peer.
	 */

	switch (pci_pcie_type(dev)) {
	case PCI_EXP_TYPE_ENDPOINT:
	case PCI_EXP_TYPE_LEG_END:
	case PCI_EXP_TYPE_RC_END:
		break;
	default:
		return -EINVAL;
	}

	while (bus->parent) {
		bridge = bus->self;

		pcie_capability_read_dword(bridge, PCI_EXP_DEVCAP2, &cap);

		switch (pci_pcie_type(bridge)) {
		/* Ensure switch ports support AtomicOp routing */
		case PCI_EXP_TYPE_UPSTREAM:
		case PCI_EXP_TYPE_DOWNSTREAM:
			if (!(cap & PCI_EXP_DEVCAP2_ATOMIC_ROUTE))
				return -EINVAL;
			break;

		/* Ensure root port supports all the sizes we care about */
		case PCI_EXP_TYPE_ROOT_PORT:
			if ((cap & cap_mask) != cap_mask)
				return -EINVAL;
			break;
		}

		/* Ensure upstream ports don't block AtomicOps on egress */
		if (pci_pcie_type(bridge) == PCI_EXP_TYPE_UPSTREAM) {
			pcie_capability_read_dword(bridge, PCI_EXP_DEVCTL2,
						   &ctl2);
			if (ctl2 & PCI_EXP_DEVCTL2_ATOMIC_EGRESS_BLOCK)
				return -EINVAL;
		}

		bus = bus->parent;
	}

	pcie_capability_set_word(dev, PCI_EXP_DEVCTL2,
				 PCI_EXP_DEVCTL2_ATOMIC_REQ);
	return 0;
}