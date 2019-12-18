#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  ide_hwif_t ;
struct TYPE_5__ {size_t dma_mode; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 size_t const XFER_MW_DMA_0 ; 
 scalar_t__ ide_get_drivedata (TYPE_1__*) ; 
 int /*<<< orphan*/  ide_set_drivedata (TYPE_1__*,void*) ; 

__attribute__((used)) static void sl82c105_set_dma_mode(ide_hwif_t *hwif, ide_drive_t *drive)
{
	static u16 mwdma_timings[] = {0x0707, 0x0201, 0x0200};
	unsigned long timings = (unsigned long)ide_get_drivedata(drive);
	u16 drv_ctrl;
	const u8 speed = drive->dma_mode;

	drv_ctrl = mwdma_timings[speed - XFER_MW_DMA_0];

	/*
	 * Store the DMA timings so that we can actually program
	 * them when DMA will be turned on...
	 */
	timings &= 0x0000ffff;
	timings |= (unsigned long)drv_ctrl << 16;
	ide_set_drivedata(drive, (void *)timings);
}