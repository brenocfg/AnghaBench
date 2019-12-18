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
struct nd_region {int /*<<< orphan*/ * bb_state; int /*<<< orphan*/ * dax_seed; int /*<<< orphan*/ * pfn_seed; int /*<<< orphan*/ * btt_seed; int /*<<< orphan*/ * ns_seed; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  child_unregister ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_for_each_child (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (struct device*) ; 
 int /*<<< orphan*/  sysfs_put (int /*<<< orphan*/ *) ; 
 struct nd_region* to_nd_region (struct device*) ; 

__attribute__((used)) static int nd_region_remove(struct device *dev)
{
	struct nd_region *nd_region = to_nd_region(dev);

	device_for_each_child(dev, NULL, child_unregister);

	/* flush attribute readers and disable */
	nvdimm_bus_lock(dev);
	nd_region->ns_seed = NULL;
	nd_region->btt_seed = NULL;
	nd_region->pfn_seed = NULL;
	nd_region->dax_seed = NULL;
	dev_set_drvdata(dev, NULL);
	nvdimm_bus_unlock(dev);

	/*
	 * Note, this assumes nd_device_lock() context to not race
	 * nd_region_notify()
	 */
	sysfs_put(nd_region->bb_state);
	nd_region->bb_state = NULL;

	return 0;
}