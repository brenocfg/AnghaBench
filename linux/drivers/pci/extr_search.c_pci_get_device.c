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
 int /*<<< orphan*/  PCI_ANY_ID ; 
 struct pci_dev* pci_get_subsys (unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 

struct pci_dev *pci_get_device(unsigned int vendor, unsigned int device,
			       struct pci_dev *from)
{
	return pci_get_subsys(vendor, device, PCI_ANY_ID, PCI_ANY_ID, from);
}