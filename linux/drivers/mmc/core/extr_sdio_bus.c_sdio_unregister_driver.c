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
struct TYPE_2__ {int /*<<< orphan*/ * bus; } ;
struct sdio_driver {TYPE_1__ drv; } ;

/* Variables and functions */
 int /*<<< orphan*/  driver_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  sdio_bus_type ; 

void sdio_unregister_driver(struct sdio_driver *drv)
{
	drv->drv.bus = &sdio_bus_type;
	driver_unregister(&drv->drv);
}