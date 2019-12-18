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
typedef  int /*<<< orphan*/  u32 ;
struct pcie_port_service_driver {scalar_t__ (* reset_link ) (struct pci_dev*) ;} ;
struct pci_dev {int dummy; } ;
typedef  scalar_t__ pci_ers_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 scalar_t__ PCI_ERS_RESULT_DISCONNECT ; 
 scalar_t__ PCI_ERS_RESULT_RECOVERED ; 
 scalar_t__ default_reset_link (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_printk (int /*<<< orphan*/ ,struct pci_dev*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pcie_downstream_port (struct pci_dev*) ; 
 struct pcie_port_service_driver* pcie_port_find_service (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct pci_dev*) ; 

__attribute__((used)) static pci_ers_result_t reset_link(struct pci_dev *dev, u32 service)
{
	pci_ers_result_t status;
	struct pcie_port_service_driver *driver = NULL;

	driver = pcie_port_find_service(dev, service);
	if (driver && driver->reset_link) {
		status = driver->reset_link(dev);
	} else if (pcie_downstream_port(dev)) {
		status = default_reset_link(dev);
	} else {
		pci_printk(KERN_DEBUG, dev, "no link-reset support at upstream device %s\n",
			pci_name(dev));
		return PCI_ERS_RESULT_DISCONNECT;
	}

	if (status != PCI_ERS_RESULT_RECOVERED) {
		pci_printk(KERN_DEBUG, dev, "link reset at upstream device %s failed\n",
			pci_name(dev));
		return PCI_ERS_RESULT_DISCONNECT;
	}

	return status;
}