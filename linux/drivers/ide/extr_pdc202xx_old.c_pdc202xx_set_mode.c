#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_7__ {int dn; int dma_mode; scalar_t__ media; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
#define  XFER_MW_DMA_0 141 
#define  XFER_MW_DMA_1 140 
#define  XFER_MW_DMA_2 139 
#define  XFER_PIO_0 138 
#define  XFER_PIO_1 137 
#define  XFER_PIO_2 136 
#define  XFER_PIO_3 135 
#define  XFER_PIO_4 134 
 int const XFER_SW_DMA_0 ; 
#define  XFER_UDMA_0 133 
#define  XFER_UDMA_1 132 
#define  XFER_UDMA_2 131 
#define  XFER_UDMA_3 130 
#define  XFER_UDMA_4 129 
#define  XFER_UDMA_5 128 
 scalar_t__ ide_disk ; 
 scalar_t__ ide_pio_need_iordy (TYPE_2__*,int const) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pdc202xx_set_mode(ide_hwif_t *hwif, ide_drive_t *drive)
{
	struct pci_dev *dev	= to_pci_dev(hwif->dev);
	u8 drive_pci		= 0x60 + (drive->dn << 2);
	const u8 speed		= drive->dma_mode;

	u8			AP = 0, BP = 0, CP = 0;
	u8			TA = 0, TB = 0, TC = 0;

	pci_read_config_byte(dev, drive_pci,     &AP);
	pci_read_config_byte(dev, drive_pci + 1, &BP);
	pci_read_config_byte(dev, drive_pci + 2, &CP);

	switch(speed) {
		case XFER_UDMA_5:
		case XFER_UDMA_4:	TB = 0x20; TC = 0x01; break;
		case XFER_UDMA_2:	TB = 0x20; TC = 0x01; break;
		case XFER_UDMA_3:
		case XFER_UDMA_1:	TB = 0x40; TC = 0x02; break;
		case XFER_UDMA_0:
		case XFER_MW_DMA_2:	TB = 0x60; TC = 0x03; break;
		case XFER_MW_DMA_1:	TB = 0x60; TC = 0x04; break;
		case XFER_MW_DMA_0:	TB = 0xE0; TC = 0x0F; break;
		case XFER_PIO_4:	TA = 0x01; TB = 0x04; break;
		case XFER_PIO_3:	TA = 0x02; TB = 0x06; break;
		case XFER_PIO_2:	TA = 0x03; TB = 0x08; break;
		case XFER_PIO_1:	TA = 0x05; TB = 0x0C; break;
		case XFER_PIO_0:
		default:		TA = 0x09; TB = 0x13; break;
	}

	if (speed < XFER_SW_DMA_0) {
		/*
		 * preserve SYNC_INT / ERDDY_EN bits while clearing
		 * Prefetch_EN / IORDY_EN / PA[3:0] bits of register A
		 */
		AP &= ~0x3f;
		if (ide_pio_need_iordy(drive, speed - XFER_PIO_0))
			AP |= 0x20;	/* set IORDY_EN bit */
		if (drive->media == ide_disk)
			AP |= 0x10;	/* set Prefetch_EN bit */
		/* clear PB[4:0] bits of register B */
		BP &= ~0x1f;
		pci_write_config_byte(dev, drive_pci,     AP | TA);
		pci_write_config_byte(dev, drive_pci + 1, BP | TB);
	} else {
		/* clear MB[2:0] bits of register B */
		BP &= ~0xe0;
		/* clear MC[3:0] bits of register C */
		CP &= ~0x0f;
		pci_write_config_byte(dev, drive_pci + 1, BP | TB);
		pci_write_config_byte(dev, drive_pci + 2, CP | TC);
	}
}