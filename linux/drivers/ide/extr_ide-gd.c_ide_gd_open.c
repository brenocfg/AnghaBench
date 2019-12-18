#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ide_disk_obj {int openers; TYPE_2__* drive; } ;
struct gendisk {int dummy; } ;
struct block_device {struct gendisk* bd_disk; } ;
struct TYPE_6__ {int dev_flags; TYPE_1__* disk_ops; } ;
typedef  TYPE_2__ ide_drive_t ;
typedef  int fmode_t ;
struct TYPE_5__ {int (* init_media ) (TYPE_2__*,struct gendisk*) ;int /*<<< orphan*/  (* set_doorlock ) (TYPE_2__*,struct gendisk*,int) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ENXIO ; 
 int EROFS ; 
 int FMODE_NDELAY ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  IDE_DBG_FUNC ; 
 int IDE_DFLAG_FORMAT_IN_PROGRESS ; 
 int IDE_DFLAG_MEDIA_CHANGED ; 
 int IDE_DFLAG_REMOVABLE ; 
 int IDE_DFLAG_WP ; 
 int /*<<< orphan*/  check_disk_change (struct block_device*) ; 
 int /*<<< orphan*/  ide_debug_log (int /*<<< orphan*/ ,char*) ; 
 struct ide_disk_obj* ide_disk_get (struct gendisk*) ; 
 int /*<<< orphan*/  ide_disk_put (struct ide_disk_obj*) ; 
 int stub1 (TYPE_2__*,struct gendisk*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,struct gendisk*,int) ; 

__attribute__((used)) static int ide_gd_open(struct block_device *bdev, fmode_t mode)
{
	struct gendisk *disk = bdev->bd_disk;
	struct ide_disk_obj *idkp;
	ide_drive_t *drive;
	int ret = 0;

	idkp = ide_disk_get(disk);
	if (idkp == NULL)
		return -ENXIO;

	drive = idkp->drive;

	ide_debug_log(IDE_DBG_FUNC, "enter");

	idkp->openers++;

	if ((drive->dev_flags & IDE_DFLAG_REMOVABLE) && idkp->openers == 1) {
		drive->dev_flags &= ~IDE_DFLAG_FORMAT_IN_PROGRESS;
		/* Just in case */

		ret = drive->disk_ops->init_media(drive, disk);

		/*
		 * Allow O_NDELAY to open a drive without a disk, or with an
		 * unreadable disk, so that we can get the format capacity
		 * of the drive or begin the format - Sam
		 */
		if (ret && (mode & FMODE_NDELAY) == 0) {
			ret = -EIO;
			goto out_put_idkp;
		}

		if ((drive->dev_flags & IDE_DFLAG_WP) && (mode & FMODE_WRITE)) {
			ret = -EROFS;
			goto out_put_idkp;
		}

		/*
		 * Ignore the return code from door_lock,
		 * since the open() has already succeeded,
		 * and the door_lock is irrelevant at this point.
		 */
		drive->disk_ops->set_doorlock(drive, disk, 1);
		drive->dev_flags |= IDE_DFLAG_MEDIA_CHANGED;
		check_disk_change(bdev);
	} else if (drive->dev_flags & IDE_DFLAG_FORMAT_IN_PROGRESS) {
		ret = -EBUSY;
		goto out_put_idkp;
	}
	return 0;

out_put_idkp:
	idkp->openers--;
	ide_disk_put(idkp);
	return ret;
}