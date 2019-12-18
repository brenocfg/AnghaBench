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
typedef  int u8 ;
struct pci_device_id {int driver_data; } ;
struct pci_dev {int revision; } ;
struct ide_port_info {int /*<<< orphan*/  host_flags; scalar_t__ swdma_mask; scalar_t__ mwdma_mask; int /*<<< orphan*/ * dma_ops; int /*<<< orphan*/  udma_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_UDMA2 ; 
 int /*<<< orphan*/  ATA_UDMA4 ; 
 int /*<<< orphan*/  ATA_UDMA5 ; 
 int /*<<< orphan*/  ATA_UDMA6 ; 
 int /*<<< orphan*/  IDE_HFLAG_CLEAR_SIMPLEX ; 
 int /*<<< orphan*/  IDE_HFLAG_NO_ATAPI_DMA ; 
 int /*<<< orphan*/  IDE_HFLAG_NO_DMA ; 
 int /*<<< orphan*/  IDE_HFLAG_NO_LBA48_DMA ; 
 struct ide_port_info ali15x3_chipset ; 
 int /*<<< orphan*/  ali_dma_ops ; 
 int ide_pci_init_one (struct pci_dev*,struct ide_port_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alim15x3_init_one(struct pci_dev *dev,
			     const struct pci_device_id *id)
{
	struct ide_port_info d = ali15x3_chipset;
	u8 rev = dev->revision, idx = id->driver_data;

	/* don't use LBA48 DMA on ALi devices before rev 0xC5 */
	if (rev <= 0xC4)
		d.host_flags |= IDE_HFLAG_NO_LBA48_DMA;

	if (rev >= 0x20) {
		if (rev == 0x20)
			d.host_flags |= IDE_HFLAG_NO_ATAPI_DMA;

		if (rev < 0xC2)
			d.udma_mask = ATA_UDMA2;
		else if (rev == 0xC2 || rev == 0xC3)
			d.udma_mask = ATA_UDMA4;
		else if (rev == 0xC4)
			d.udma_mask = ATA_UDMA5;
		else
			d.udma_mask = ATA_UDMA6;

		d.dma_ops = &ali_dma_ops;
	} else {
		d.host_flags |= IDE_HFLAG_NO_DMA;

		d.mwdma_mask = d.swdma_mask = 0;
	}

	if (idx == 0)
		d.host_flags |= IDE_HFLAG_CLEAR_SIMPLEX;

	return ide_pci_init_one(dev, &d, NULL);
}