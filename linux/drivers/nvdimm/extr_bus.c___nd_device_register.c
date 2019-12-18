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
struct device {struct device* parent; int /*<<< orphan*/ * bus; } ;
struct TYPE_2__ {scalar_t__ numa_node; } ;

/* Variables and functions */
 scalar_t__ NUMA_NO_NODE ; 
 int /*<<< orphan*/  async_schedule_dev_domain (int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ *) ; 
 scalar_t__ dev_to_node (struct device*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 scalar_t__ is_nd_region (struct device*) ; 
 int /*<<< orphan*/  nd_async_device_register ; 
 int /*<<< orphan*/  nd_async_domain ; 
 int /*<<< orphan*/  nvdimm_bus_type ; 
 int /*<<< orphan*/  set_dev_node (struct device*,scalar_t__) ; 
 TYPE_1__* to_nd_region (struct device*) ; 

void __nd_device_register(struct device *dev)
{
	if (!dev)
		return;

	/*
	 * Ensure that region devices always have their NUMA node set as
	 * early as possible. This way we are able to make certain that
	 * any memory associated with the creation and the creation
	 * itself of the region is associated with the correct node.
	 */
	if (is_nd_region(dev))
		set_dev_node(dev, to_nd_region(dev)->numa_node);

	dev->bus = &nvdimm_bus_type;
	if (dev->parent) {
		get_device(dev->parent);
		if (dev_to_node(dev) == NUMA_NO_NODE)
			set_dev_node(dev, dev_to_node(dev->parent));
	}
	get_device(dev);

	async_schedule_dev_domain(nd_async_device_register, dev,
				  &nd_async_domain);
}