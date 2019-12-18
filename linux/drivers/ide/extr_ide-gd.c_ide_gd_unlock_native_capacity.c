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
struct ide_disk_ops {int /*<<< orphan*/  (* unlock_native_capacity ) (TYPE_1__*) ;} ;
struct ide_disk_obj {TYPE_1__* drive; } ;
struct gendisk {int dummy; } ;
struct TYPE_3__ {struct ide_disk_ops* disk_ops; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  ide_disk_obj ; 
 struct ide_disk_obj* ide_drv_g (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void ide_gd_unlock_native_capacity(struct gendisk *disk)
{
	struct ide_disk_obj *idkp = ide_drv_g(disk, ide_disk_obj);
	ide_drive_t *drive = idkp->drive;
	const struct ide_disk_ops *disk_ops = drive->disk_ops;

	if (disk_ops->unlock_native_capacity)
		disk_ops->unlock_native_capacity(drive);
}