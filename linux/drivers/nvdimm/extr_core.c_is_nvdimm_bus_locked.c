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
struct nvdimm_bus {int /*<<< orphan*/  reconfig_mutex; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int mutex_is_locked (int /*<<< orphan*/ *) ; 
 struct nvdimm_bus* walk_to_nvdimm_bus (struct device*) ; 

bool is_nvdimm_bus_locked(struct device *dev)
{
	struct nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);

	if (!nvdimm_bus)
		return false;
	return mutex_is_locked(&nvdimm_bus->reconfig_mutex);
}