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
typedef  int u32 ;
struct pci_dev {int class; } ;

/* Variables and functions */
 int PCI_CLASS_STORAGE_SCSI ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,int,int) ; 

__attribute__((used)) static void fixup_rev1_53c810(struct pci_dev *dev)
{
	u32 class = dev->class;

	/*
	 * rev 1 ncr53c810 chips don't set the class at all which means
	 * they don't get their resources remapped. Fix that here.
	 */
	if (class)
		return;

	dev->class = PCI_CLASS_STORAGE_SCSI << 8;
	pci_info(dev, "NCR 53c810 rev 1 PCI class overridden (%#08x -> %#08x)\n",
		 class, dev->class);
}