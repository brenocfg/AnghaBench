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
struct TYPE_6__ {unsigned long config_data; int /*<<< orphan*/ * expiry; int /*<<< orphan*/  rq; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_7__ {scalar_t__ dn; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int SECTOR_SIZE ; 
 unsigned long blk_rq_sectors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_dma_start (TYPE_2__*) ; 
 int /*<<< orphan*/  ide_set_hwifdata (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outw (int,unsigned long) ; 
 int /*<<< orphan*/  tc86c001_timer_expiry ; 

__attribute__((used)) static void tc86c001_dma_start(ide_drive_t *drive)
{
	ide_hwif_t *hwif	= drive->hwif;
	unsigned long sc_base	= hwif->config_data;
	unsigned long twcr_port	= sc_base + (drive->dn ? 0x06 : 0x04);
	unsigned long nsectors	= blk_rq_sectors(hwif->rq);

	/*
	 * We have to manually load the sector count and size into
	 * the appropriate system control registers for DMA to work
	 * with LBA48 and ATAPI devices...
	 */
	outw(nsectors, sc_base + 0x0a);	/* Sector Count */
	outw(SECTOR_SIZE / 2, twcr_port); /* Transfer Word Count 1/2 */

	/* Install our timeout expiry hook, saving the current handler... */
	ide_set_hwifdata(hwif, hwif->expiry);
	hwif->expiry = &tc86c001_timer_expiry;

	ide_dma_start(drive);
}