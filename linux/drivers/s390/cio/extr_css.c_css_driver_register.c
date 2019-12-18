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
struct css_driver {TYPE_1__ drv; } ;

/* Variables and functions */
 int /*<<< orphan*/  css_bus_type ; 
 int driver_register (TYPE_1__*) ; 

int css_driver_register(struct css_driver *cdrv)
{
	cdrv->drv.bus = &css_bus_type;
	return driver_register(&cdrv->drv);
}