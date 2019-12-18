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
struct pci_dev {int /*<<< orphan*/  dma_alias_mask; struct pci_dev* driver_override; int /*<<< orphan*/  bus; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_bus_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_capabilities (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_of_node (struct pci_dev*) ; 
 int /*<<< orphan*/  pcibios_release_device (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static void pci_release_dev(struct device *dev)
{
	struct pci_dev *pci_dev;

	pci_dev = to_pci_dev(dev);
	pci_release_capabilities(pci_dev);
	pci_release_of_node(pci_dev);
	pcibios_release_device(pci_dev);
	pci_bus_put(pci_dev->bus);
	kfree(pci_dev->driver_override);
	bitmap_free(pci_dev->dma_alias_mask);
	kfree(pci_dev);
}