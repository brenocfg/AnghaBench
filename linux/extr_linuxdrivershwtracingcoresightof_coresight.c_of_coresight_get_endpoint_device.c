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
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amba_bustype ; 
 struct device* bus_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_dev_node_match ; 
 int /*<<< orphan*/  platform_bus_type ; 

__attribute__((used)) static struct device *
of_coresight_get_endpoint_device(struct device_node *endpoint)
{
	struct device *dev = NULL;

	/*
	 * If we have a non-configurable replicator, it will be found on the
	 * platform bus.
	 */
	dev = bus_find_device(&platform_bus_type, NULL,
			      endpoint, of_dev_node_match);
	if (dev)
		return dev;

	/*
	 * We have a configurable component - circle through the AMBA bus
	 * looking for the device that matches the endpoint node.
	 */
	return bus_find_device(&amba_bustype, NULL,
			       endpoint, of_dev_node_match);
}