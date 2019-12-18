#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct TYPE_3__ {TYPE_2__** devices; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_4__ {int dev_flags; scalar_t__ media; } ;
typedef  TYPE_2__ ide_drive_t ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int IDE_DFLAG_PRESENT ; 
 int PARTN_BITS ; 
 scalar_t__ ide_cdrom ; 
 scalar_t__ ide_disk ; 
 scalar_t__ ide_floppy ; 
 scalar_t__ ide_optical ; 
 scalar_t__ ide_tape ; 
 int /*<<< orphan*/  request_module (char*) ; 

__attribute__((used)) static struct kobject *ata_probe(dev_t dev, int *part, void *data)
{
	ide_hwif_t *hwif = data;
	int unit = *part >> PARTN_BITS;
	ide_drive_t *drive = hwif->devices[unit];

	if ((drive->dev_flags & IDE_DFLAG_PRESENT) == 0)
		return NULL;

	if (drive->media == ide_disk)
		request_module("ide-disk");
	if (drive->media == ide_cdrom || drive->media == ide_optical)
		request_module("ide-cd");
	if (drive->media == ide_tape)
		request_module("ide-tape");
	if (drive->media == ide_floppy)
		request_module("ide-floppy");

	return NULL;
}