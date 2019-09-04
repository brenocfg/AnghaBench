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

/* Variables and functions */

__attribute__((used)) static void ide_generic_check_pci_legacy_iobases(int *primary, int *secondary)
{
#ifdef CONFIG_PCI
	struct pci_dev *p = NULL;
	u16 val;

	for_each_pci_dev(p) {
		if (pci_resource_start(p, 0) == 0x1f0)
			*primary = 1;
		if (pci_resource_start(p, 2) == 0x170)
			*secondary = 1;

		/* Cyrix CS55{1,2}0 pre SFF MWDMA ATA on the bridge */
		if (p->vendor == PCI_VENDOR_ID_CYRIX &&
		    (p->device == PCI_DEVICE_ID_CYRIX_5510 ||
		     p->device == PCI_DEVICE_ID_CYRIX_5520))
			*primary = *secondary = 1;

		/* Intel MPIIX - PIO ATA on non PCI side of bridge */
		if (p->vendor == PCI_VENDOR_ID_INTEL &&
		    p->device == PCI_DEVICE_ID_INTEL_82371MX) {
			pci_read_config_word(p, 0x6C, &val);
			if (val & 0x8000) {
				/* ATA port enabled */
				if (val & 0x4000)
					*secondary = 1;
				else
					*primary = 1;
			}
		}
	}
#endif
}