#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ide_driver {int /*<<< orphan*/  (* remove ) (int /*<<< orphan*/ *) ;} ;
struct device {int /*<<< orphan*/  driver; } ;
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * to_ide_device (struct device*) ; 
 struct ide_driver* to_ide_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int generic_ide_remove(struct device *dev)
{
	ide_drive_t *drive = to_ide_device(dev);
	struct ide_driver *drv = to_ide_driver(dev->driver);

	if (drv->remove)
		drv->remove(drive);

	return 0;
}