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
struct TYPE_6__ {scalar_t__ channel; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_7__ {int dn; int dma_mode; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int UDIDETCR0 ; 
 int UDIDETCR1 ; 
#define  XFER_MW_DMA_0 136 
#define  XFER_MW_DMA_1 135 
#define  XFER_MW_DMA_2 134 
#define  XFER_UDMA_0 133 
#define  XFER_UDMA_1 132 
#define  XFER_UDMA_2 131 
#define  XFER_UDMA_3 130 
#define  XFER_UDMA_4 129 
#define  XFER_UDMA_5 128 
 int /*<<< orphan*/  cmd64x_program_timings (TYPE_2__*,int const) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmd64x_set_dma_mode(ide_hwif_t *hwif, ide_drive_t *drive)
{
	struct pci_dev *dev	= to_pci_dev(hwif->dev);
	u8 unit			= drive->dn & 0x01;
	u8 regU = 0, pciU	= hwif->channel ? UDIDETCR1 : UDIDETCR0;
	const u8 speed		= drive->dma_mode;

	pci_read_config_byte(dev, pciU, &regU);
	regU &= ~(unit ? 0xCA : 0x35);

	switch(speed) {
	case XFER_UDMA_5:
		regU |= unit ? 0x0A : 0x05;
		break;
	case XFER_UDMA_4:
		regU |= unit ? 0x4A : 0x15;
		break;
	case XFER_UDMA_3:
		regU |= unit ? 0x8A : 0x25;
		break;
	case XFER_UDMA_2:
		regU |= unit ? 0x42 : 0x11;
		break;
	case XFER_UDMA_1:
		regU |= unit ? 0x82 : 0x21;
		break;
	case XFER_UDMA_0:
		regU |= unit ? 0xC2 : 0x31;
		break;
	case XFER_MW_DMA_2:
	case XFER_MW_DMA_1:
	case XFER_MW_DMA_0:
		cmd64x_program_timings(drive, speed);
		break;
	}

	pci_write_config_byte(dev, pciU, regU);
}