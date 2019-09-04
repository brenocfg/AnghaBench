#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct TYPE_5__ {int channel; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_6__ {int dma_mode; int dn; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int const XFER_MW_DMA_0 ; 
 int const XFER_UDMA_0 ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int const,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void svwks_set_dma_mode(ide_hwif_t *hwif, ide_drive_t *drive)
{
	static const u8 udma_modes[]		= { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05 };
	static const u8 dma_modes[]		= { 0x77, 0x21, 0x20 };
	static const u8 drive_pci2[]		= { 0x45, 0x44, 0x47, 0x46 };

	struct pci_dev *dev	= to_pci_dev(hwif->dev);
	const u8 speed		= drive->dma_mode;
	u8 unit			= drive->dn & 1;

	u8 ultra_enable	 = 0, ultra_timing = 0, dma_timing = 0;

	pci_read_config_byte(dev, (0x56|hwif->channel), &ultra_timing);
	pci_read_config_byte(dev, 0x54, &ultra_enable);

	ultra_timing	&= ~(0x0F << (4*unit));
	ultra_enable	&= ~(0x01 << drive->dn);

	if (speed >= XFER_UDMA_0) {
		dma_timing   |= dma_modes[2];
		ultra_timing |= (udma_modes[speed - XFER_UDMA_0] << (4 * unit));
		ultra_enable |= (0x01 << drive->dn);
	} else if (speed >= XFER_MW_DMA_0)
		dma_timing   |= dma_modes[speed - XFER_MW_DMA_0];

	pci_write_config_byte(dev, drive_pci2[drive->dn], dma_timing);
	pci_write_config_byte(dev, (0x56|hwif->channel), ultra_timing);
	pci_write_config_byte(dev, 0x54, ultra_enable);
}