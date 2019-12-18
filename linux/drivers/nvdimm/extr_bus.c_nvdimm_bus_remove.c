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
struct nvdimm_bus {int /*<<< orphan*/  dev; } ;
struct nd_device_driver {int (* remove ) (struct device*) ;} ;
struct module {int dummy; } ;
struct device {TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_nvdimm_lock (struct device*) ; 
 int /*<<< orphan*/  debug_nvdimm_unlock (struct device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 int stub1 (struct device*) ; 
 struct module* to_bus_provider (struct device*) ; 
 struct nd_device_driver* to_nd_device_driver (TYPE_1__*) ; 
 struct nvdimm_bus* walk_to_nvdimm_bus (struct device*) ; 

__attribute__((used)) static int nvdimm_bus_remove(struct device *dev)
{
	struct nd_device_driver *nd_drv = to_nd_device_driver(dev->driver);
	struct module *provider = to_bus_provider(dev);
	struct nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);
	int rc = 0;

	if (nd_drv->remove) {
		debug_nvdimm_lock(dev);
		rc = nd_drv->remove(dev);
		debug_nvdimm_unlock(dev);
	}

	dev_dbg(&nvdimm_bus->dev, "%s.remove(%s) = %d\n", dev->driver->name,
			dev_name(dev), rc);
	module_put(provider);
	return rc;
}