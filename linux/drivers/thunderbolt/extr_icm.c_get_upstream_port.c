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
struct pci_dev {int device; } ;

/* Variables and functions */
#define  PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_2C_BRIDGE 134 
#define  PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_4C_BRIDGE 133 
#define  PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_2C_BRIDGE 132 
#define  PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_4C_BRIDGE 131 
#define  PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_LP_BRIDGE 130 
#define  PCI_DEVICE_ID_INTEL_TITAN_RIDGE_2C_BRIDGE 129 
#define  PCI_DEVICE_ID_INTEL_TITAN_RIDGE_4C_BRIDGE 128 
 scalar_t__ PCI_EXP_TYPE_UPSTREAM ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 scalar_t__ pci_pcie_type (struct pci_dev*) ; 
 struct pci_dev* pci_upstream_bridge (struct pci_dev*) ; 

__attribute__((used)) static struct pci_dev *get_upstream_port(struct pci_dev *pdev)
{
	struct pci_dev *parent;

	parent = pci_upstream_bridge(pdev);
	while (parent) {
		if (!pci_is_pcie(parent))
			return NULL;
		if (pci_pcie_type(parent) == PCI_EXP_TYPE_UPSTREAM)
			break;
		parent = pci_upstream_bridge(parent);
	}

	if (!parent)
		return NULL;

	switch (parent->device) {
	case PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_2C_BRIDGE:
	case PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_4C_BRIDGE:
	case PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_LP_BRIDGE:
	case PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_4C_BRIDGE:
	case PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_2C_BRIDGE:
	case PCI_DEVICE_ID_INTEL_TITAN_RIDGE_2C_BRIDGE:
	case PCI_DEVICE_ID_INTEL_TITAN_RIDGE_4C_BRIDGE:
		return parent;
	}

	return NULL;
}