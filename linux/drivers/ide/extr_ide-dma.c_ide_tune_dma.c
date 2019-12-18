#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_8__ {int host_flags; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_9__ {int dev_flags; int /*<<< orphan*/  id; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int IDE_DFLAG_NODMA ; 
 int IDE_HFLAG_TRUST_BIOS_FOR_DMA ; 
 scalar_t__ __ide_dma_bad_drive (TYPE_2__*) ; 
 scalar_t__ ata_id_has_dma (int /*<<< orphan*/ ) ; 
 int config_drive_for_dma (TYPE_2__*) ; 
 int /*<<< orphan*/  ide_max_dma_mode (TYPE_2__*) ; 
 scalar_t__ ide_set_dma_mode (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ide_tune_dma(ide_drive_t *drive)
{
	ide_hwif_t *hwif = drive->hwif;
	u8 speed;

	if (ata_id_has_dma(drive->id) == 0 ||
	    (drive->dev_flags & IDE_DFLAG_NODMA))
		return 0;

	/* consult the list of known "bad" drives */
	if (__ide_dma_bad_drive(drive))
		return 0;

	if (hwif->host_flags & IDE_HFLAG_TRUST_BIOS_FOR_DMA)
		return config_drive_for_dma(drive);

	speed = ide_max_dma_mode(drive);

	if (!speed)
		return 0;

	if (ide_set_dma_mode(drive, speed))
		return 0;

	return 1;
}