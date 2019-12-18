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
struct intel_th_driver {TYPE_1__ driver; int /*<<< orphan*/  remove; int /*<<< orphan*/  probe; } ;

/* Variables and functions */
 int EINVAL ; 
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  intel_th_bus ; 

int intel_th_driver_register(struct intel_th_driver *thdrv)
{
	if (!thdrv->probe || !thdrv->remove)
		return -EINVAL;

	thdrv->driver.bus = &intel_th_bus;

	return driver_register(&thdrv->driver);
}