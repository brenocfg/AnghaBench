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
struct nd_region {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  nd_device_lock (struct device*) ; 
 int /*<<< orphan*/  nd_device_unlock (struct device*) ; 
 unsigned long long nd_region_available_dpa (struct nd_region*) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long) ; 
 struct nd_region* to_nd_region (struct device*) ; 
 int /*<<< orphan*/  wait_nvdimm_bus_probe_idle (struct device*) ; 

__attribute__((used)) static ssize_t available_size_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct nd_region *nd_region = to_nd_region(dev);
	unsigned long long available = 0;

	/*
	 * Flush in-flight updates and grab a snapshot of the available
	 * size.  Of course, this value is potentially invalidated the
	 * memory nvdimm_bus_lock() is dropped, but that's userspace's
	 * problem to not race itself.
	 */
	nd_device_lock(dev);
	nvdimm_bus_lock(dev);
	wait_nvdimm_bus_probe_idle(dev);
	available = nd_region_available_dpa(nd_region);
	nvdimm_bus_unlock(dev);
	nd_device_unlock(dev);

	return sprintf(buf, "%llu\n", available);
}