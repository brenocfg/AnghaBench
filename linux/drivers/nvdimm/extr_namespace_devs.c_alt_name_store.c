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
struct device {int /*<<< orphan*/  parent; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ __alt_name_store (struct device*,char const*,size_t) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  nd_device_lock (struct device*) ; 
 int /*<<< orphan*/  nd_device_unlock (struct device*) ; 
 scalar_t__ nd_namespace_label_update (struct nd_region*,struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (struct device*) ; 
 struct nd_region* to_nd_region (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_nvdimm_bus_probe_idle (struct device*) ; 

__attribute__((used)) static ssize_t alt_name_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t len)
{
	struct nd_region *nd_region = to_nd_region(dev->parent);
	ssize_t rc;

	nd_device_lock(dev);
	nvdimm_bus_lock(dev);
	wait_nvdimm_bus_probe_idle(dev);
	rc = __alt_name_store(dev, buf, len);
	if (rc >= 0)
		rc = nd_namespace_label_update(nd_region, dev);
	dev_dbg(dev, "%s(%zd)\n", rc < 0 ? "fail " : "", rc);
	nvdimm_bus_unlock(dev);
	nd_device_unlock(dev);

	return rc < 0 ? rc : len;
}