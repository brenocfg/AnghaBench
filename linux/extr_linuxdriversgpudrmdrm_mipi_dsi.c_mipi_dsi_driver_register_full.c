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
struct TYPE_2__ {int /*<<< orphan*/  shutdown; int /*<<< orphan*/  remove; int /*<<< orphan*/  probe; struct module* owner; int /*<<< orphan*/ * bus; } ;
struct mipi_dsi_driver {TYPE_1__ driver; scalar_t__ shutdown; scalar_t__ remove; scalar_t__ probe; } ;

/* Variables and functions */
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  mipi_dsi_bus_type ; 
 int /*<<< orphan*/  mipi_dsi_drv_probe ; 
 int /*<<< orphan*/  mipi_dsi_drv_remove ; 
 int /*<<< orphan*/  mipi_dsi_drv_shutdown ; 

int mipi_dsi_driver_register_full(struct mipi_dsi_driver *drv,
				  struct module *owner)
{
	drv->driver.bus = &mipi_dsi_bus_type;
	drv->driver.owner = owner;

	if (drv->probe)
		drv->driver.probe = mipi_dsi_drv_probe;
	if (drv->remove)
		drv->driver.remove = mipi_dsi_drv_remove;
	if (drv->shutdown)
		drv->driver.shutdown = mipi_dsi_drv_shutdown;

	return driver_register(&drv->driver);
}