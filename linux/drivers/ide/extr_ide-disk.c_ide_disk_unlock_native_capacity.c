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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {int dev_flags; int /*<<< orphan*/  probed_capacity; int /*<<< orphan*/ * id; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int IDE_DFLAG_LBA ; 
 int IDE_DFLAG_NOHPA ; 
 scalar_t__ ata_id_hpa_enabled (int /*<<< orphan*/ *) ; 
 int ata_id_lba48_enabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ide_disk_hpa_get_native_capacity (TYPE_1__*,int) ; 
 scalar_t__ ide_disk_hpa_set_capacity (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ide_disk_unlock_native_capacity(ide_drive_t *drive)
{
	u16 *id = drive->id;
	int lba48 = ata_id_lba48_enabled(id);

	if ((drive->dev_flags & IDE_DFLAG_LBA) == 0 ||
	    ata_id_hpa_enabled(id) == 0)
		return;

	/*
	 * according to the spec the SET MAX ADDRESS command shall be
	 * immediately preceded by a READ NATIVE MAX ADDRESS command
	 */
	if (!ide_disk_hpa_get_native_capacity(drive, lba48))
		return;

	if (ide_disk_hpa_set_capacity(drive, drive->probed_capacity, lba48))
		drive->dev_flags |= IDE_DFLAG_NOHPA; /* disable HPA on resume */
}