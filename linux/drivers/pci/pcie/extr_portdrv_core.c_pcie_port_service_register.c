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
struct TYPE_2__ {int /*<<< orphan*/  shutdown; int /*<<< orphan*/  remove; int /*<<< orphan*/  probe; int /*<<< orphan*/ * bus; int /*<<< orphan*/  name; } ;
struct pcie_port_service_driver {TYPE_1__ driver; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  pcie_port_bus_type ; 
 int /*<<< orphan*/  pcie_port_probe_service ; 
 int /*<<< orphan*/  pcie_port_remove_service ; 
 int /*<<< orphan*/  pcie_port_shutdown_service ; 
 scalar_t__ pcie_ports_disabled ; 

int pcie_port_service_register(struct pcie_port_service_driver *new)
{
	if (pcie_ports_disabled)
		return -ENODEV;

	new->driver.name = new->name;
	new->driver.bus = &pcie_port_bus_type;
	new->driver.probe = pcie_port_probe_service;
	new->driver.remove = pcie_port_remove_service;
	new->driver.shutdown = pcie_port_shutdown_service;

	return driver_register(&new->driver);
}