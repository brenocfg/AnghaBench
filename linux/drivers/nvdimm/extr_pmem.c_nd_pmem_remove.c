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
struct pmem_device {int /*<<< orphan*/ * bb_state; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct pmem_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ is_nd_btt (struct device*) ; 
 int /*<<< orphan*/  nvdimm_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvdimm_namespace_detach_btt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_nd_btt (struct device*) ; 
 int /*<<< orphan*/  to_nd_region (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nd_pmem_remove(struct device *dev)
{
	struct pmem_device *pmem = dev_get_drvdata(dev);

	if (is_nd_btt(dev))
		nvdimm_namespace_detach_btt(to_nd_btt(dev));
	else {
		/*
		 * Note, this assumes nd_device_lock() context to not
		 * race nd_pmem_notify()
		 */
		sysfs_put(pmem->bb_state);
		pmem->bb_state = NULL;
	}
	nvdimm_flush(to_nd_region(dev->parent), NULL);

	return 0;
}