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

/* Variables and functions */
 int PCI_IOV_RESOURCES ; 
 int PCI_IOV_RESOURCE_END ; 
 int PCI_ROM_RESOURCE ; 
 int /*<<< orphan*/  pci_iov_update_resource (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_std_update_resource (struct pci_dev*,int) ; 

void pci_update_resource(struct pci_dev *dev, int resno)
{
	if (resno <= PCI_ROM_RESOURCE)
		pci_std_update_resource(dev, resno);
#ifdef CONFIG_PCI_IOV
	else if (resno >= PCI_IOV_RESOURCES && resno <= PCI_IOV_RESOURCE_END)
		pci_iov_update_resource(dev, resno);
#endif
}