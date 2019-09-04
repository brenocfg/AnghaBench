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
struct device_driver {int /*<<< orphan*/  name; TYPE_1__* bus; } ;
typedef  int /*<<< orphan*/  async_cookie_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int driver_attach (struct device_driver*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void driver_attach_async(void *_drv, async_cookie_t cookie)
{
	struct device_driver *drv = _drv;
	int ret;

	ret = driver_attach(drv);

	pr_debug("bus: '%s': driver %s async attach completed: %d\n",
		 drv->bus->name, drv->name, ret);
}