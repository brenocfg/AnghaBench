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
struct seq_file {scalar_t__ private; } ;
struct ide_driver {int /*<<< orphan*/  version; } ;
struct device {TYPE_2__* driver; } ;
struct TYPE_3__ {struct device gendev; } ;
typedef  TYPE_1__ ide_drive_t ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 struct ide_driver* to_ide_driver (TYPE_2__*) ; 

__attribute__((used)) static int ide_driver_proc_show(struct seq_file *m, void *v)
{
	ide_drive_t		*drive = (ide_drive_t *)m->private;
	struct device		*dev = &drive->gendev;
	struct ide_driver	*ide_drv;

	if (dev->driver) {
		ide_drv = to_ide_driver(dev->driver);
		seq_printf(m, "%s version %s\n",
				dev->driver->name, ide_drv->version);
	} else
		seq_printf(m, "ide-default version 0.9.newide\n");
	return 0;
}