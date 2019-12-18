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
struct TYPE_2__ {struct module* owner; int /*<<< orphan*/ * bus; } ;
struct spmi_driver {TYPE_1__ driver; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  spmi_bus_type ; 

int __spmi_driver_register(struct spmi_driver *sdrv, struct module *owner)
{
	sdrv->driver.bus = &spmi_bus_type;
	sdrv->driver.owner = owner;
	return driver_register(&sdrv->driver);
}