#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_8__ {int dn; int dma_mode; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETC ; 
 int IDE_D0_SHIFT ; 
 int IDE_D1_SHIFT ; 
 int IDE_DRV_MASK ; 
 int IDE_ETC_UDMA_MASK ; 
 int const XFER_MW_DMA_0 ; 
 int const XFER_UDMA_0 ; 
 int /*<<< orphan*/  cs5536_read (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  cs5536_write (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ide_get_drivedata (TYPE_2__*) ; 
 int /*<<< orphan*/  ide_set_drivedata (TYPE_2__*,void*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cs5536_set_dma_mode(ide_hwif_t *hwif, ide_drive_t *drive)
{
	static const u8 udma_timings[6] = {
		0xc2, 0xc1, 0xc0, 0xc4, 0xc5, 0xc6,
	};

	static const u8 mwdma_timings[3] = {
		0x67, 0x21, 0x20,
	};

	struct pci_dev *pdev = to_pci_dev(hwif->dev);
	int dshift = (drive->dn & 1) ? IDE_D1_SHIFT : IDE_D0_SHIFT;
	unsigned long timings = (unsigned long)ide_get_drivedata(drive);
	u32 etc;
	const u8 mode = drive->dma_mode;

	cs5536_read(pdev, ETC, &etc);

	if (mode >= XFER_UDMA_0) {
		etc &= ~(IDE_DRV_MASK << dshift);
		etc |= udma_timings[mode - XFER_UDMA_0] << dshift;
	} else { /* MWDMA */
		etc &= ~(IDE_ETC_UDMA_MASK << dshift);
		timings &= IDE_DRV_MASK;
		timings |= mwdma_timings[mode - XFER_MW_DMA_0] << 8;
		ide_set_drivedata(drive, (void *)timings);
	}

	cs5536_write(pdev, ETC, etc);
}