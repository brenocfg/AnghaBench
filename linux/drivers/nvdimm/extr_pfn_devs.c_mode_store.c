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
struct nd_pfn {int /*<<< orphan*/  mode; } ;
struct device_attribute {int dummy; } ;
struct device {scalar_t__ driver; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  PFN_MODE_NONE ; 
 int /*<<< orphan*/  PFN_MODE_PMEM ; 
 int /*<<< orphan*/  PFN_MODE_RAM ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,char const*,char*) ; 
 int /*<<< orphan*/  nd_device_lock (struct device*) ; 
 int /*<<< orphan*/  nd_device_unlock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (struct device*) ; 
 scalar_t__ strncmp (char const*,char*,size_t) ; 
 struct nd_pfn* to_nd_pfn_safe (struct device*) ; 

__attribute__((used)) static ssize_t mode_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t len)
{
	struct nd_pfn *nd_pfn = to_nd_pfn_safe(dev);
	ssize_t rc = 0;

	nd_device_lock(dev);
	nvdimm_bus_lock(dev);
	if (dev->driver)
		rc = -EBUSY;
	else {
		size_t n = len - 1;

		if (strncmp(buf, "pmem\n", n) == 0
				|| strncmp(buf, "pmem", n) == 0) {
			nd_pfn->mode = PFN_MODE_PMEM;
		} else if (strncmp(buf, "ram\n", n) == 0
				|| strncmp(buf, "ram", n) == 0)
			nd_pfn->mode = PFN_MODE_RAM;
		else if (strncmp(buf, "none\n", n) == 0
				|| strncmp(buf, "none", n) == 0)
			nd_pfn->mode = PFN_MODE_NONE;
		else
			rc = -EINVAL;
	}
	dev_dbg(dev, "result: %zd wrote: %s%s", rc, buf,
			buf[len - 1] == '\n' ? "" : "\n");
	nvdimm_bus_unlock(dev);
	nd_device_unlock(dev);

	return rc ? rc : len;
}