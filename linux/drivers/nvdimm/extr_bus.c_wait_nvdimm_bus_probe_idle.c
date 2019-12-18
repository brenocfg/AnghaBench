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
struct nvdimm_bus {scalar_t__ probe_active; int /*<<< orphan*/  wait; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nd_device_lock (struct device*) ; 
 int /*<<< orphan*/  nd_device_unlock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (struct device*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 struct nvdimm_bus* walk_to_nvdimm_bus (struct device*) ; 

void wait_nvdimm_bus_probe_idle(struct device *dev)
{
	struct nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);

	do {
		if (nvdimm_bus->probe_active == 0)
			break;
		nvdimm_bus_unlock(dev);
		nd_device_unlock(dev);
		wait_event(nvdimm_bus->wait,
				nvdimm_bus->probe_active == 0);
		nd_device_lock(dev);
		nvdimm_bus_lock(dev);
	} while (true);
}