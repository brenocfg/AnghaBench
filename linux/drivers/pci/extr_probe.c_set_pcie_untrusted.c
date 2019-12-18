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
struct pci_dev {int untrusted; } ;

/* Variables and functions */
 struct pci_dev* pci_upstream_bridge (struct pci_dev*) ; 

__attribute__((used)) static void set_pcie_untrusted(struct pci_dev *dev)
{
	struct pci_dev *parent;

	/*
	 * If the upstream bridge is untrusted we treat this device
	 * untrusted as well.
	 */
	parent = pci_upstream_bridge(dev);
	if (parent && parent->untrusted)
		dev->untrusted = true;
}