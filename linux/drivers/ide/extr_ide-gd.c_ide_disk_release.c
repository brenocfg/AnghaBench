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
struct ide_disk_obj {struct gendisk* disk; TYPE_1__* drive; } ;
struct gendisk {int /*<<< orphan*/ * private_data; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * driver_data; int /*<<< orphan*/ * disk_ops; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  ide_disk_obj ; 
 int /*<<< orphan*/  kfree (struct ide_disk_obj*) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 struct ide_disk_obj* to_ide_drv (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ide_disk_release(struct device *dev)
{
	struct ide_disk_obj *idkp = to_ide_drv(dev, ide_disk_obj);
	ide_drive_t *drive = idkp->drive;
	struct gendisk *g = idkp->disk;

	drive->disk_ops = NULL;
	drive->driver_data = NULL;
	g->private_data = NULL;
	put_disk(g);
	kfree(idkp);
}