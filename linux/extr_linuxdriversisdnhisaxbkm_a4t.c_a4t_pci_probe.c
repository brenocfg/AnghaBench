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
typedef  int u_int ;
typedef  scalar_t__ u16 ;
struct pci_dev {scalar_t__ subsystem_vendor; scalar_t__ subsystem_device; int /*<<< orphan*/  irq; } ;
struct IsdnCardState {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_BERKOM_A4T ; 
 scalar_t__ PCI_VENDOR_ID_BERKOM ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int a4t_pci_probe(struct pci_dev *dev_a4t, struct IsdnCardState *cs,
			 u_int *found, u_int *pci_memaddr)
{
	u16 sub_sys;
	u16 sub_vendor;

	sub_vendor = dev_a4t->subsystem_vendor;
	sub_sys = dev_a4t->subsystem_device;
	if ((sub_sys == PCI_DEVICE_ID_BERKOM_A4T) && (sub_vendor == PCI_VENDOR_ID_BERKOM)) {
		if (pci_enable_device(dev_a4t))
			return (0);	/* end loop & function */
		*found = 1;
		*pci_memaddr = pci_resource_start(dev_a4t, 0);
		cs->irq = dev_a4t->irq;
		return (1);		/* end loop */
	}

	return (-1);			/* continue looping */
}