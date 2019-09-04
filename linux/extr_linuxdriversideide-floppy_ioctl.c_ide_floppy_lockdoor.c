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
struct ide_disk_obj {int openers; struct gendisk* disk; } ;
struct ide_atapi_pc {int dummy; } ;
struct gendisk {int dummy; } ;
struct TYPE_5__ {struct ide_disk_obj* driver_data; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 unsigned int CDROMEJECT ; 
 int EBUSY ; 
 int /*<<< orphan*/  ide_do_start_stop (TYPE_1__*,struct gendisk*,int) ; 
 int /*<<< orphan*/  ide_set_media_lock (TYPE_1__*,struct gendisk*,int) ; 

__attribute__((used)) static int ide_floppy_lockdoor(ide_drive_t *drive, struct ide_atapi_pc *pc,
			       unsigned long arg, unsigned int cmd)
{
	struct ide_disk_obj *floppy = drive->driver_data;
	struct gendisk *disk = floppy->disk;
	int prevent = (arg && cmd != CDROMEJECT) ? 1 : 0;

	if (floppy->openers > 1)
		return -EBUSY;

	ide_set_media_lock(drive, disk, prevent);

	if (cmd == CDROMEJECT)
		ide_do_start_stop(drive, disk, 2);

	return 0;
}