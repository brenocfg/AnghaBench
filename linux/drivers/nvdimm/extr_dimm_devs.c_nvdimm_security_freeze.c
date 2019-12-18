#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ flags; TYPE_2__* ops; } ;
struct nvdimm {TYPE_1__ sec; int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int (* freeze ) (struct nvdimm*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NDD_SECURITY_OVERWRITE ; 
 int /*<<< orphan*/  NVDIMM_USER ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  is_nvdimm_bus_locked (int /*<<< orphan*/ *) ; 
 scalar_t__ nvdimm_security_flags (struct nvdimm*,int /*<<< orphan*/ ) ; 
 int stub1 (struct nvdimm*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nvdimm_security_freeze(struct nvdimm *nvdimm)
{
	int rc;

	WARN_ON_ONCE(!is_nvdimm_bus_locked(&nvdimm->dev));

	if (!nvdimm->sec.ops || !nvdimm->sec.ops->freeze)
		return -EOPNOTSUPP;

	if (!nvdimm->sec.flags)
		return -EIO;

	if (test_bit(NDD_SECURITY_OVERWRITE, &nvdimm->flags)) {
		dev_warn(&nvdimm->dev, "Overwrite operation in progress.\n");
		return -EBUSY;
	}

	rc = nvdimm->sec.ops->freeze(nvdimm);
	nvdimm->sec.flags = nvdimm_security_flags(nvdimm, NVDIMM_USER);

	return rc;
}