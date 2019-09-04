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
typedef  int u32 ;
struct pci_dev {int class; int /*<<< orphan*/  devfn; TYPE_1__* resource; } ;
struct TYPE_2__ {scalar_t__ flags; scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_BASE_ADDRESS_0 ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_1 ; 
 int PCI_BASE_ADDRESS_SPACE_IO ; 
 int PCI_CLASS_STORAGE_IDE ; 
 scalar_t__ PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pci_fixup_cy82c693(struct pci_dev *dev)
{
	if ((dev->class >> 8) == PCI_CLASS_STORAGE_IDE) {
		u32 base0, base1;

		if (dev->class & 0x80) {	/* primary */
			base0 = 0x1f0;
			base1 = 0x3f4;
		} else {			/* secondary */
			base0 = 0x170;
			base1 = 0x374;
		}

		pci_write_config_dword(dev, PCI_BASE_ADDRESS_0,
				       base0 | PCI_BASE_ADDRESS_SPACE_IO);
		pci_write_config_dword(dev, PCI_BASE_ADDRESS_1,
				       base1 | PCI_BASE_ADDRESS_SPACE_IO);

		dev->resource[0].start = 0;
		dev->resource[0].end   = 0;
		dev->resource[0].flags = 0;

		dev->resource[1].start = 0;
		dev->resource[1].end   = 0;
		dev->resource[1].flags = 0;
	} else if (PCI_FUNC(dev->devfn) == 0) {
		/*
		 * Setup IDE IRQ routing.
		 */
		pci_write_config_byte(dev, 0x4b, 14);
		pci_write_config_byte(dev, 0x4c, 15);

		/*
		 * Disable FREQACK handshake, enable USB.
		 */
		pci_write_config_byte(dev, 0x4d, 0x41);

		/*
		 * Enable PCI retry, and PCI post-write buffer.
		 */
		pci_write_config_byte(dev, 0x44, 0x17);

		/*
		 * Enable ISA master and DMA post write buffering.
		 */
		pci_write_config_byte(dev, 0x45, 0x03);
	}
}