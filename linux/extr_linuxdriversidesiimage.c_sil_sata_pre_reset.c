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
struct TYPE_3__ {scalar_t__ media; int special_flags; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int IDE_SFLAG_RECALIBRATE ; 
 int IDE_SFLAG_SET_GEOMETRY ; 
 scalar_t__ ide_disk ; 

__attribute__((used)) static void sil_sata_pre_reset(ide_drive_t *drive)
{
	if (drive->media == ide_disk) {
		drive->special_flags &=
			~(IDE_SFLAG_SET_GEOMETRY | IDE_SFLAG_RECALIBRATE);
	}
}