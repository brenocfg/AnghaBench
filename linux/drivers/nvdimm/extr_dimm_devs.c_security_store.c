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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  nd_device_lock (struct device*) ; 
 int /*<<< orphan*/  nd_device_unlock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_security_store (struct device*,char const*,size_t) ; 
 int /*<<< orphan*/  wait_nvdimm_bus_probe_idle (struct device*) ; 

__attribute__((used)) static ssize_t security_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t len)

{
	ssize_t rc;

	/*
	 * Require all userspace triggered security management to be
	 * done while probing is idle and the DIMM is not in active use
	 * in any region.
	 */
	nd_device_lock(dev);
	nvdimm_bus_lock(dev);
	wait_nvdimm_bus_probe_idle(dev);
	rc = nvdimm_security_store(dev, buf, len);
	nvdimm_bus_unlock(dev);
	nd_device_unlock(dev);

	return rc;
}