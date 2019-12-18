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
struct nd_region {int dummy; } ;
struct nd_namespace_pmem {unsigned long lbasize; } ;
struct nd_namespace_blk {unsigned long lbasize; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int ssize_t ;
struct TYPE_2__ {scalar_t__ claim; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENXIO ; 
 unsigned long* blk_lbasize_supported ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,char*,char const*,char*) ; 
 scalar_t__ is_namespace_blk (struct device*) ; 
 scalar_t__ is_namespace_pmem (struct device*) ; 
 int /*<<< orphan*/  nd_device_lock (struct device*) ; 
 int /*<<< orphan*/  nd_device_unlock (struct device*) ; 
 int nd_namespace_label_update (struct nd_region*,struct device*) ; 
 int nd_size_select_store (struct device*,char const*,unsigned long*,unsigned long const*) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (struct device*) ; 
 unsigned long* pmem_lbasize_supported ; 
 struct nd_namespace_blk* to_nd_namespace_blk (struct device*) ; 
 struct nd_namespace_pmem* to_nd_namespace_pmem (struct device*) ; 
 struct nd_region* to_nd_region (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_ndns (struct device*) ; 

__attribute__((used)) static ssize_t sector_size_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t len)
{
	struct nd_region *nd_region = to_nd_region(dev->parent);
	const unsigned long *supported;
	unsigned long *lbasize;
	ssize_t rc = 0;

	if (is_namespace_blk(dev)) {
		struct nd_namespace_blk *nsblk = to_nd_namespace_blk(dev);

		lbasize = &nsblk->lbasize;
		supported = blk_lbasize_supported;
	} else if (is_namespace_pmem(dev)) {
		struct nd_namespace_pmem *nspm = to_nd_namespace_pmem(dev);

		lbasize = &nspm->lbasize;
		supported = pmem_lbasize_supported;
	} else
		return -ENXIO;

	nd_device_lock(dev);
	nvdimm_bus_lock(dev);
	if (to_ndns(dev)->claim)
		rc = -EBUSY;
	if (rc >= 0)
		rc = nd_size_select_store(dev, buf, lbasize, supported);
	if (rc >= 0)
		rc = nd_namespace_label_update(nd_region, dev);
	dev_dbg(dev, "result: %zd %s: %s%s", rc, rc < 0 ? "tried" : "wrote",
			buf, buf[len - 1] == '\n' ? "" : "\n");
	nvdimm_bus_unlock(dev);
	nd_device_unlock(dev);

	return rc ? rc : len;
}