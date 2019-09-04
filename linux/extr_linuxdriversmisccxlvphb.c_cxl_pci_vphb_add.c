#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_controller {TYPE_3__* bus; int /*<<< orphan*/  controller_ops; struct cxl_afu* private_data; int /*<<< orphan*/ * cfg_data; int /*<<< orphan*/ * cfg_addr; int /*<<< orphan*/ * ops; struct device* parent; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct cxl_afu {struct pci_controller* phb; TYPE_2__* adapter; int /*<<< orphan*/  crs_num; } ;
struct TYPE_7__ {int /*<<< orphan*/  bridge; } ;
struct TYPE_5__ {struct device* parent; } ;
struct TYPE_6__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  cxl_pci_controller_ops ; 
 int /*<<< orphan*/  cxl_pcie_pci_ops ; 
 int /*<<< orphan*/  pci_bus_add_devices (TYPE_3__*) ; 
 int /*<<< orphan*/  pci_set_host_bridge_release (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 struct pci_controller* pcibios_alloc_controller (struct device_node*) ; 
 int /*<<< orphan*/  pcibios_claim_one_bus (TYPE_3__*) ; 
 int /*<<< orphan*/  pcibios_free_controller_deferred ; 
 int /*<<< orphan*/  pcibios_scan_phb (struct pci_controller*) ; 
 int /*<<< orphan*/  to_pci_host_bridge (int /*<<< orphan*/ ) ; 

int cxl_pci_vphb_add(struct cxl_afu *afu)
{
	struct pci_controller *phb;
	struct device_node *vphb_dn;
	struct device *parent;

	/*
	 * If there are no AFU configuration records we won't have anything to
	 * expose under the vPHB, so skip creating one, returning success since
	 * this is still a valid case. This will also opt us out of EEH
	 * handling since we won't have anything special to do if there are no
	 * kernel drivers attached to the vPHB, and EEH handling is not yet
	 * supported in the peer model.
	 */
	if (!afu->crs_num)
		return 0;

	/* The parent device is the adapter. Reuse the device node of
	 * the adapter.
	 * We don't seem to care what device node is used for the vPHB,
	 * but tools such as lsvpd walk up the device parents looking
	 * for a valid location code, so we might as well show devices
	 * attached to the adapter as being located on that adapter.
	 */
	parent = afu->adapter->dev.parent;
	vphb_dn = parent->of_node;

	/* Alloc and setup PHB data structure */
	phb = pcibios_alloc_controller(vphb_dn);
	if (!phb)
		return -ENODEV;

	/* Setup parent in sysfs */
	phb->parent = parent;

	/* Setup the PHB using arch provided callback */
	phb->ops = &cxl_pcie_pci_ops;
	phb->cfg_addr = NULL;
	phb->cfg_data = NULL;
	phb->private_data = afu;
	phb->controller_ops = cxl_pci_controller_ops;

	/* Scan the bus */
	pcibios_scan_phb(phb);
	if (phb->bus == NULL)
		return -ENXIO;

	/* Set release hook on root bus */
	pci_set_host_bridge_release(to_pci_host_bridge(phb->bus->bridge),
				    pcibios_free_controller_deferred,
				    (void *) phb);

	/* Claim resources. This might need some rework as well depending
	 * whether we are doing probe-only or not, like assigning unassigned
	 * resources etc...
	 */
	pcibios_claim_one_bus(phb->bus);

	/* Add probed PCI devices to the device model */
	pci_bus_add_devices(phb->bus);

	afu->phb = phb;

	return 0;
}