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
struct sdio_driver {TYPE_1__ drv; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  sdio_bus_type ; 

int sdio_register_driver(struct sdio_driver *drv)
{
	drv->drv.name = drv->name;
	drv->drv.bus = &sdio_bus_type;
	return driver_register(&drv->drv);
}