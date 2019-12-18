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
typedef  int u16 ;
struct pci_dev {scalar_t__ hdr_type; scalar_t__ is_busmaster; scalar_t__ msi_enabled; scalar_t__ msix_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_INVALIDATE ; 
 scalar_t__ PCI_HEADER_TYPE_NORMAL ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msix (struct pci_dev*) ; 
 scalar_t__ pci_is_enabled (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xen_pcibk_control_isr (struct pci_dev*,int) ; 

void xen_pcibk_reset_device(struct pci_dev *dev)
{
	u16 cmd;

	xen_pcibk_control_isr(dev, 1 /* reset device */);

	/* Disable devices (but not bridges) */
	if (dev->hdr_type == PCI_HEADER_TYPE_NORMAL) {
#ifdef CONFIG_PCI_MSI
		/* The guest could have been abruptly killed without
		 * disabling MSI/MSI-X interrupts.*/
		if (dev->msix_enabled)
			pci_disable_msix(dev);
		if (dev->msi_enabled)
			pci_disable_msi(dev);
#endif
		if (pci_is_enabled(dev))
			pci_disable_device(dev);

		dev->is_busmaster = 0;
	} else {
		pci_read_config_word(dev, PCI_COMMAND, &cmd);
		if (cmd & (PCI_COMMAND_INVALIDATE)) {
			cmd &= ~(PCI_COMMAND_INVALIDATE);
			pci_write_config_word(dev, PCI_COMMAND, cmd);

			dev->is_busmaster = 0;
		}
	}
}