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
struct module {int dummy; } ;
struct TYPE_2__ {struct module* owner; int /*<<< orphan*/ * bus; } ;
struct apr_driver {TYPE_1__ driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  aprbus ; 
 int driver_register (TYPE_1__*) ; 

int __apr_driver_register(struct apr_driver *drv, struct module *owner)
{
	drv->driver.bus = &aprbus;
	drv->driver.owner = owner;

	return driver_register(&drv->driver);
}