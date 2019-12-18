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
struct pci_dev {scalar_t__ subsystem_vendor; int subsystem_device; int d3_delay; } ;

/* Variables and functions */
 scalar_t__ PCI_VENDOR_ID_APPLE ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,int) ; 

__attribute__((used)) static void quirk_radeon_pm(struct pci_dev *dev)
{
	if (dev->subsystem_vendor == PCI_VENDOR_ID_APPLE &&
	    dev->subsystem_device == 0x00e2) {
		if (dev->d3_delay < 20) {
			dev->d3_delay = 20;
			pci_info(dev, "extending delay after power-on from D3 to %d msec\n",
				 dev->d3_delay);
		}
	}
}