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
typedef  scalar_t__ u16 ;
struct pci_dev_acs_ops {scalar_t__ vendor; scalar_t__ device; int (* enable_acs ) (struct pci_dev*) ;} ;
struct pci_dev {scalar_t__ vendor; scalar_t__ device; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct pci_dev_acs_ops*) ; 
 int ENOTTY ; 
 scalar_t__ PCI_ANY_ID ; 
 struct pci_dev_acs_ops* pci_dev_acs_ops ; 
 int stub1 (struct pci_dev*) ; 

int pci_dev_specific_enable_acs(struct pci_dev *dev)
{
	const struct pci_dev_acs_ops *p;
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(pci_dev_acs_ops); i++) {
		p = &pci_dev_acs_ops[i];
		if ((p->vendor == dev->vendor ||
		     p->vendor == (u16)PCI_ANY_ID) &&
		    (p->device == dev->device ||
		     p->device == (u16)PCI_ANY_ID) &&
		    p->enable_acs) {
			ret = p->enable_acs(dev);
			if (ret >= 0)
				return ret;
		}
	}

	return -ENOTTY;
}