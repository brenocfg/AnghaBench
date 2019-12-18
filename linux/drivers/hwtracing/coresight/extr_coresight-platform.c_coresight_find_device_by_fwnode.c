#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fwnode_handle {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amba_bustype ; 
 struct device* bus_find_device_by_fwnode (int /*<<< orphan*/ *,struct fwnode_handle*) ; 
 int /*<<< orphan*/  platform_bus_type ; 

__attribute__((used)) static struct device *
coresight_find_device_by_fwnode(struct fwnode_handle *fwnode)
{
	struct device *dev = NULL;

	/*
	 * If we have a non-configurable replicator, it will be found on the
	 * platform bus.
	 */
	dev = bus_find_device_by_fwnode(&platform_bus_type, fwnode);
	if (dev)
		return dev;

	/*
	 * We have a configurable component - circle through the AMBA bus
	 * looking for the device that matches the endpoint node.
	 */
	return bus_find_device_by_fwnode(&amba_bustype, fwnode);
}