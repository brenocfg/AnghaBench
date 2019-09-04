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
struct TYPE_2__ {int /*<<< orphan*/ * bus; int /*<<< orphan*/  name; } ;
struct cx_drv {TYPE_1__ driver; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  tiocx_bus_type ; 

int cx_driver_register(struct cx_drv *cx_driver)
{
	cx_driver->driver.name = cx_driver->name;
	cx_driver->driver.bus = &tiocx_bus_type;

	return driver_register(&cx_driver->driver);
}