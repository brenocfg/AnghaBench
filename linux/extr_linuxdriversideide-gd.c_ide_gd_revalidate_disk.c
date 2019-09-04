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
struct ide_disk_obj {TYPE_2__* drive; } ;
struct gendisk {int dummy; } ;
struct TYPE_6__ {TYPE_1__* disk_ops; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_capacity ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ide_disk_obj ; 
 struct ide_disk_obj* ide_drv_g (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_gd_capacity (TYPE_2__*) ; 
 scalar_t__ ide_gd_check_events (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_capacity (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static int ide_gd_revalidate_disk(struct gendisk *disk)
{
	struct ide_disk_obj *idkp = ide_drv_g(disk, ide_disk_obj);
	ide_drive_t *drive = idkp->drive;

	if (ide_gd_check_events(disk, 0))
		drive->disk_ops->get_capacity(drive);

	set_capacity(disk, ide_gd_capacity(drive));
	return 0;
}