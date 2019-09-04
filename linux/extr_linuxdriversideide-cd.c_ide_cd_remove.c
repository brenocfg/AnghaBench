#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cdrom_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  disk; int /*<<< orphan*/  driver; } ;
struct TYPE_4__ {struct cdrom_info* driver_data; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDE_DBG_FUNC ; 
 int /*<<< orphan*/  del_gendisk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ide_debug_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ide_proc_unregister_driver (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idecd_ref_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ide_cd_remove(ide_drive_t *drive)
{
	struct cdrom_info *info = drive->driver_data;

	ide_debug_log(IDE_DBG_FUNC, "enter");

	ide_proc_unregister_driver(drive, info->driver);
	device_del(&info->dev);
	del_gendisk(info->disk);

	mutex_lock(&idecd_ref_mutex);
	put_device(&info->dev);
	mutex_unlock(&idecd_ref_mutex);
}