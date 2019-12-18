#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int revision; TYPE_1__* subordinate; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_BUS_FLAGS_NO_MMRBC ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,int) ; 

__attribute__((used)) static void quirk_amd_8131_mmrbc(struct pci_dev *dev)
{
	if (dev->subordinate && dev->revision <= 0x12) {
		pci_info(dev, "AMD8131 rev %x detected; disabling PCI-X MMRBC\n",
			 dev->revision);
		dev->subordinate->bus_flags |= PCI_BUS_FLAGS_NO_MMRBC;
	}
}