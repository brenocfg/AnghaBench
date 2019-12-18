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
struct pci_dev {scalar_t__ subsystem_vendor; int subsystem_device; scalar_t__ device; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ PCI_VENDOR_ID_HP ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void quirk_diva_aux_disable(struct pci_dev *dev)
{
	if (dev->subsystem_vendor != PCI_VENDOR_ID_HP ||
	    dev->subsystem_device != 0x1291)
		return;

	dev_info(&dev->dev, "Hiding Diva built-in AUX serial device");
	dev->device = 0;
}