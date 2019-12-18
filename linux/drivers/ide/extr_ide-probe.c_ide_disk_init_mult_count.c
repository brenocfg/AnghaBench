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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_3__ {int* id; int mult_req; int /*<<< orphan*/  special_flags; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 size_t ATA_ID_MAX_MULTSECT ; 
 size_t ATA_ID_MULTSECT ; 
 int /*<<< orphan*/  IDE_SFLAG_SET_MULTMODE ; 

__attribute__((used)) static void ide_disk_init_mult_count(ide_drive_t *drive)
{
	u16 *id = drive->id;
	u8 max_multsect = id[ATA_ID_MAX_MULTSECT] & 0xff;

	if (max_multsect) {
		if ((max_multsect / 2) > 1)
			id[ATA_ID_MULTSECT] = max_multsect | 0x100;
		else
			id[ATA_ID_MULTSECT] &= ~0x1ff;

		drive->mult_req = id[ATA_ID_MULTSECT] & 0xff;

		if (drive->mult_req)
			drive->special_flags |= IDE_SFLAG_SET_MULTMODE;
	}
}