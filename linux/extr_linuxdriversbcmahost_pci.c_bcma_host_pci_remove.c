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
struct pci_dev {int dummy; } ;
struct bcma_bus {int /*<<< orphan*/  mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcma_bus_unregister (struct bcma_bus*) ; 
 int /*<<< orphan*/  kfree (struct bcma_bus*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct bcma_bus* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 

__attribute__((used)) static void bcma_host_pci_remove(struct pci_dev *dev)
{
	struct bcma_bus *bus = pci_get_drvdata(dev);

	bcma_bus_unregister(bus);
	pci_iounmap(dev, bus->mmio);
	pci_release_regions(dev);
	pci_disable_device(dev);
	kfree(bus);
}