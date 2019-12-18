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
struct nvdimm {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int __nvdimm_security_unlock (struct nvdimm*) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (struct device*) ; 
 struct nvdimm* to_nvdimm (struct device*) ; 

int nvdimm_security_unlock(struct device *dev)
{
	struct nvdimm *nvdimm = to_nvdimm(dev);
	int rc;

	nvdimm_bus_lock(dev);
	rc = __nvdimm_security_unlock(nvdimm);
	nvdimm_bus_unlock(dev);
	return rc;
}