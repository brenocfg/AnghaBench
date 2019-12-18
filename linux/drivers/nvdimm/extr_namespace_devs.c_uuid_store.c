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
typedef  int /*<<< orphan*/  u8 ;
struct nd_region {int dummy; } ;
struct nd_namespace_pmem {int /*<<< orphan*/ * uuid; } ;
struct nd_namespace_blk {int /*<<< orphan*/ * uuid; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {scalar_t__ claim; } ;

/* Variables and functions */
 size_t EBUSY ; 
 size_t ENXIO ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,size_t,char const*,char*) ; 
 scalar_t__ is_namespace_blk (struct device*) ; 
 scalar_t__ is_namespace_pmem (struct device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 size_t namespace_update_uuid (struct nd_region*,struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nd_device_lock (struct device*) ; 
 int /*<<< orphan*/  nd_device_unlock (struct device*) ; 
 size_t nd_namespace_label_update (struct nd_region*,struct device*) ; 
 size_t nd_uuid_store (struct device*,int /*<<< orphan*/ **,char const*,size_t) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (struct device*) ; 
 struct nd_namespace_blk* to_nd_namespace_blk (struct device*) ; 
 struct nd_namespace_pmem* to_nd_namespace_pmem (struct device*) ; 
 struct nd_region* to_nd_region (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_ndns (struct device*) ; 
 int /*<<< orphan*/  wait_nvdimm_bus_probe_idle (struct device*) ; 

__attribute__((used)) static ssize_t uuid_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t len)
{
	struct nd_region *nd_region = to_nd_region(dev->parent);
	u8 *uuid = NULL;
	ssize_t rc = 0;
	u8 **ns_uuid;

	if (is_namespace_pmem(dev)) {
		struct nd_namespace_pmem *nspm = to_nd_namespace_pmem(dev);

		ns_uuid = &nspm->uuid;
	} else if (is_namespace_blk(dev)) {
		struct nd_namespace_blk *nsblk = to_nd_namespace_blk(dev);

		ns_uuid = &nsblk->uuid;
	} else
		return -ENXIO;

	nd_device_lock(dev);
	nvdimm_bus_lock(dev);
	wait_nvdimm_bus_probe_idle(dev);
	if (to_ndns(dev)->claim)
		rc = -EBUSY;
	if (rc >= 0)
		rc = nd_uuid_store(dev, &uuid, buf, len);
	if (rc >= 0)
		rc = namespace_update_uuid(nd_region, dev, uuid, ns_uuid);
	if (rc >= 0)
		rc = nd_namespace_label_update(nd_region, dev);
	else
		kfree(uuid);
	dev_dbg(dev, "result: %zd wrote: %s%s", rc, buf,
			buf[len - 1] == '\n' ? "" : "\n");
	nvdimm_bus_unlock(dev);
	nd_device_unlock(dev);

	return rc < 0 ? rc : len;
}