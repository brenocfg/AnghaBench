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
struct TYPE_6__ {int extra_base; scalar_t__ channel; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_7__ {scalar_t__ media; int dev_flags; scalar_t__ current_speed; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int IDE_DFLAG_LBA48 ; 
 scalar_t__ XFER_UDMA_2 ; 
 scalar_t__ ide_disk ; 
 int ide_dma_end (TYPE_2__*) ; 
 int inb (unsigned long) ; 
 int /*<<< orphan*/  outb (int,unsigned long) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pdc_old_disable_66MHz_clock (TYPE_1__*) ; 

__attribute__((used)) static int pdc202xx_dma_end(ide_drive_t *drive)
{
	if (drive->media != ide_disk || (drive->dev_flags & IDE_DFLAG_LBA48)) {
		ide_hwif_t *hwif	= drive->hwif;
		unsigned long high_16	= hwif->extra_base - 16;
		unsigned long atapi_reg	= high_16 + (hwif->channel ? 0x24 : 0x20);
		u8 clock		= 0;

		outl(0, atapi_reg); /* zero out extra */
		clock = inb(high_16 + 0x11);
		outb(clock & ~(hwif->channel ? 0x08:0x02), high_16 + 0x11);
	}
	if (drive->current_speed > XFER_UDMA_2)
		pdc_old_disable_66MHz_clock(drive->hwif);
	return ide_dma_end(drive);
}