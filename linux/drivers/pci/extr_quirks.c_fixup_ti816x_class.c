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
 int PCI_CLASS_MULTIMEDIA_VIDEO ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,int,int) ; 

__attribute__((used)) static void fixup_ti816x_class(struct pci_dev *dev)
{
	u32 class = dev->class;

	/* TI 816x devices do not have class code set when in PCIe boot mode */
	dev->class = PCI_CLASS_MULTIMEDIA_VIDEO << 8;
	pci_info(dev, "PCI class overridden (%#08x -> %#08x)\n",
		 class, dev->class);
}