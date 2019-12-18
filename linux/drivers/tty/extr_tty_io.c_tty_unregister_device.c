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
struct tty_driver {int flags; int /*<<< orphan*/ ** cdevs; int /*<<< orphan*/  minor_start; int /*<<< orphan*/  major; } ;

/* Variables and functions */
 scalar_t__ MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TTY_DRIVER_DYNAMIC_ALLOC ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tty_class ; 

void tty_unregister_device(struct tty_driver *driver, unsigned index)
{
	device_destroy(tty_class,
		MKDEV(driver->major, driver->minor_start) + index);
	if (!(driver->flags & TTY_DRIVER_DYNAMIC_ALLOC)) {
		cdev_del(driver->cdevs[index]);
		driver->cdevs[index] = NULL;
	}
}