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
struct nvdimm_bus {int dummy; } ;
struct nd_region {int /*<<< orphan*/  dev; } ;
typedef  enum nvdimm_event { ____Placeholder_nvdimm_event } nvdimm_event ;

/* Variables and functions */
 int /*<<< orphan*/  nd_device_notify (int /*<<< orphan*/ *,int) ; 
 struct nvdimm_bus* walk_to_nvdimm_bus (int /*<<< orphan*/ *) ; 

void nvdimm_region_notify(struct nd_region *nd_region, enum nvdimm_event event)
{
	struct nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(&nd_region->dev);

	if (!nvdimm_bus)
		return;

	/* caller is responsible for holding a reference on the device */
	nd_device_notify(&nd_region->dev, event);
}