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
typedef  size_t u8 ;
struct pci_device_id {size_t driver_data; } ;
struct pci_dev {int revision; } ;
struct ide_port_info {int udma_mask; int /*<<< orphan*/ * dma_ops; int /*<<< orphan*/ * port_ops; TYPE_1__* enablebits; } ;
struct TYPE_2__ {scalar_t__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmd646_rev1_dma_ops ; 
 struct ide_port_info* cmd64x_chipsets ; 
 int /*<<< orphan*/  cmd64x_port_ops ; 
 int ide_pci_init_one (struct pci_dev*,struct ide_port_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmd64x_init_one(struct pci_dev *dev, const struct pci_device_id *id)
{
	struct ide_port_info d;
	u8 idx = id->driver_data;

	d = cmd64x_chipsets[idx];

	if (idx == 1) {
		/*
		 * UltraDMA only supported on PCI646U and PCI646U2, which
		 * correspond to revisions 0x03, 0x05 and 0x07 respectively.
		 * Actually, although the CMD tech support people won't
		 * tell me the details, the 0x03 revision cannot support
		 * UDMA correctly without hardware modifications, and even
		 * then it only works with Quantum disks due to some
		 * hold time assumptions in the 646U part which are fixed
		 * in the 646U2.
		 *
		 * So we only do UltraDMA on revision 0x05 and 0x07 chipsets.
		 */
		if (dev->revision < 5) {
			d.udma_mask = 0x00;
			/*
			 * The original PCI0646 didn't have the primary
			 * channel enable bit, it appeared starting with
			 * PCI0646U (i.e. revision ID 3).
			 */
			if (dev->revision < 3) {
				d.enablebits[0].reg = 0;
				d.port_ops = &cmd64x_port_ops;
				if (dev->revision == 1)
					d.dma_ops = &cmd646_rev1_dma_ops;
			}
		}
	}

	return ide_pci_init_one(dev, &d, NULL);
}