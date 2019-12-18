#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_3__ {int* id; int cyl; int head; int sect; int bios_cyl; int bios_head; int bios_sect; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 size_t ATA_ID_CUR_CYLS ; 
 size_t ATA_ID_CUR_HEADS ; 
 size_t ATA_ID_CUR_SECTORS ; 
 size_t ATA_ID_CYLS ; 
 size_t ATA_ID_HEADS ; 
 size_t ATA_ID_SECTORS ; 
 scalar_t__ ata_id_current_chs_valid (int*) ; 

__attribute__((used)) static void ide_disk_init_chs(ide_drive_t *drive)
{
	u16 *id = drive->id;

	/* Extract geometry if we did not already have one for the drive */
	if (!drive->cyl || !drive->head || !drive->sect) {
		drive->cyl  = drive->bios_cyl  = id[ATA_ID_CYLS];
		drive->head = drive->bios_head = id[ATA_ID_HEADS];
		drive->sect = drive->bios_sect = id[ATA_ID_SECTORS];
	}

	/* Handle logical geometry translation by the drive */
	if (ata_id_current_chs_valid(id)) {
		drive->cyl  = id[ATA_ID_CUR_CYLS];
		drive->head = id[ATA_ID_CUR_HEADS];
		drive->sect = id[ATA_ID_CUR_SECTORS];
	}

	/* Use physical geometry if what we have still makes no sense */
	if (drive->head > 16 && id[ATA_ID_HEADS] && id[ATA_ID_HEADS] <= 16) {
		drive->cyl  = id[ATA_ID_CYLS];
		drive->head = id[ATA_ID_HEADS];
		drive->sect = id[ATA_ID_SECTORS];
	}
}