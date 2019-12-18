#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ide_disk_obj {TYPE_1__* drive; } ;
struct gendisk {int dummy; } ;
struct TYPE_2__ {int dev_flags; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 unsigned int DISK_EVENT_MEDIA_CHANGE ; 
 int IDE_DFLAG_ATTACH ; 
 int IDE_DFLAG_MEDIA_CHANGED ; 
 int /*<<< orphan*/  ide_disk_obj ; 
 struct ide_disk_obj* ide_drv_g (struct gendisk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int ide_gd_check_events(struct gendisk *disk,
					unsigned int clearing)
{
	struct ide_disk_obj *idkp = ide_drv_g(disk, ide_disk_obj);
	ide_drive_t *drive = idkp->drive;
	bool ret;

	/* do not scan partitions twice if this is a removable device */
	if (drive->dev_flags & IDE_DFLAG_ATTACH) {
		drive->dev_flags &= ~IDE_DFLAG_ATTACH;
		return 0;
	}

	/*
	 * The following is used to force revalidation on the first open on
	 * removeable devices, and never gets reported to userland as
	 * DISK_EVENT_FLAG_UEVENT isn't set in genhd->event_flags.
	 * This is intended as removable ide disk can't really detect
	 * MEDIA_CHANGE events.
	 */
	ret = drive->dev_flags & IDE_DFLAG_MEDIA_CHANGED;
	drive->dev_flags &= ~IDE_DFLAG_MEDIA_CHANGED;

	return ret ? DISK_EVENT_MEDIA_CHANGE : 0;
}