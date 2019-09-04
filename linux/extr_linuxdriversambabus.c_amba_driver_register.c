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
struct TYPE_2__ {int /*<<< orphan*/  shutdown; int /*<<< orphan*/  remove; int /*<<< orphan*/  probe; int /*<<< orphan*/ * bus; } ;
struct amba_driver {TYPE_1__ drv; scalar_t__ shutdown; scalar_t__ remove; scalar_t__ probe; } ;

/* Variables and functions */
 int /*<<< orphan*/  amba_bustype ; 
 int /*<<< orphan*/  amba_probe ; 
 int /*<<< orphan*/  amba_remove ; 
 int /*<<< orphan*/  amba_shutdown ; 
 int driver_register (TYPE_1__*) ; 

int amba_driver_register(struct amba_driver *drv)
{
	drv->drv.bus = &amba_bustype;

#define SETFN(fn)	if (drv->fn) drv->drv.fn = amba_##fn
	SETFN(probe);
	SETFN(remove);
	SETFN(shutdown);

	return driver_register(&drv->drv);
}