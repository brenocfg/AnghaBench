#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct TYPE_4__ {int host_flags; scalar_t__ hwif_data; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_5__ {TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int ATA_UDMA5 ; 
 int ATA_UDMA6 ; 
 int /*<<< orphan*/  BUG () ; 
 int IDE_HFLAG_MMIO ; 
 int sil_ioread8 (struct pci_dev*,unsigned long) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 sil_pata_udma_filter(ide_drive_t *drive)
{
	ide_hwif_t *hwif	= drive->hwif;
	struct pci_dev *dev	= to_pci_dev(hwif->dev);
	unsigned long base	= (unsigned long)hwif->hwif_data;
	u8 scsc, mask		= 0;

	base += (hwif->host_flags & IDE_HFLAG_MMIO) ? 0x4A : 0x8A;

	scsc = sil_ioread8(dev, base);

	switch (scsc & 0x30) {
	case 0x10:	/* 133 */
		mask = ATA_UDMA6;
		break;
	case 0x20:	/* 2xPCI */
		mask = ATA_UDMA6;
		break;
	case 0x00:	/* 100 */
		mask = ATA_UDMA5;
		break;
	default: 	/* Disabled ? */
		BUG();
	}

	return mask;
}