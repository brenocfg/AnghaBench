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
struct ide_tape_obj {int minor; int /*<<< orphan*/  valid; struct gendisk* disk; TYPE_1__* drive; } ;
struct gendisk {int /*<<< orphan*/ * private_data; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * driver_data; int /*<<< orphan*/  dev_flags; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDETAPE_MAJOR ; 
 int /*<<< orphan*/  IDE_DFLAG_DSC_OVERLAP ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_tape_obj ; 
 int /*<<< orphan*/ ** idetape_devs ; 
 int /*<<< orphan*/  idetape_sysfs_class ; 
 int /*<<< orphan*/  kfree (struct ide_tape_obj*) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 struct ide_tape_obj* to_ide_drv (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ide_tape_release(struct device *dev)
{
	struct ide_tape_obj *tape = to_ide_drv(dev, ide_tape_obj);
	ide_drive_t *drive = tape->drive;
	struct gendisk *g = tape->disk;

	BUG_ON(tape->valid);

	drive->dev_flags &= ~IDE_DFLAG_DSC_OVERLAP;
	drive->driver_data = NULL;
	device_destroy(idetape_sysfs_class, MKDEV(IDETAPE_MAJOR, tape->minor));
	device_destroy(idetape_sysfs_class,
			MKDEV(IDETAPE_MAJOR, tape->minor + 128));
	idetape_devs[tape->minor] = NULL;
	g->private_data = NULL;
	put_disk(g);
	kfree(tape);
}