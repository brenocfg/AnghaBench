#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int coherent_dma_mask; int /*<<< orphan*/ * dma_parms; int /*<<< orphan*/ * dma_mask; int /*<<< orphan*/  release; } ;
struct pci_dev {int state_saved; int match_driver; TYPE_1__ dev; int /*<<< orphan*/  bus_list; int /*<<< orphan*/  dma_parms; int /*<<< orphan*/  dma_mask; } ;
struct pci_bus {int /*<<< orphan*/  devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int device_add (TYPE_1__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  dma_set_max_seg_size (TYPE_1__*,int) ; 
 int /*<<< orphan*/  dma_set_seg_boundary (TYPE_1__*,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_bus_sem ; 
 int /*<<< orphan*/  pci_configure_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_fixup_device (int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_fixup_header ; 
 int /*<<< orphan*/  pci_init_capabilities (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_reassigndev_resource_alignment (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_dev ; 
 int /*<<< orphan*/  pci_set_msi_domain (struct pci_dev*) ; 
 int pcibios_add_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pcibus_to_node (struct pci_bus*) ; 
 int /*<<< orphan*/  set_dev_node (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void pci_device_add(struct pci_dev *dev, struct pci_bus *bus)
{
	int ret;

	pci_configure_device(dev);

	device_initialize(&dev->dev);
	dev->dev.release = pci_release_dev;

	set_dev_node(&dev->dev, pcibus_to_node(bus));
	dev->dev.dma_mask = &dev->dma_mask;
	dev->dev.dma_parms = &dev->dma_parms;
	dev->dev.coherent_dma_mask = 0xffffffffull;

	dma_set_max_seg_size(&dev->dev, 65536);
	dma_set_seg_boundary(&dev->dev, 0xffffffff);

	/* Fix up broken headers */
	pci_fixup_device(pci_fixup_header, dev);

	/* Moved out from quirk header fixup code */
	pci_reassigndev_resource_alignment(dev);

	/* Clear the state_saved flag */
	dev->state_saved = false;

	/* Initialize various capabilities */
	pci_init_capabilities(dev);

	/*
	 * Add the device to our list of discovered devices
	 * and the bus list for fixup functions, etc.
	 */
	down_write(&pci_bus_sem);
	list_add_tail(&dev->bus_list, &bus->devices);
	up_write(&pci_bus_sem);

	ret = pcibios_add_device(dev);
	WARN_ON(ret < 0);

	/* Set up MSI IRQ domain */
	pci_set_msi_domain(dev);

	/* Notifier could use PCI capabilities */
	dev->match_driver = false;
	ret = device_add(&dev->dev);
	WARN_ON(ret < 0);
}