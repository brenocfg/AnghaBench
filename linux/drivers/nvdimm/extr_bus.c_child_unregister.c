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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct nvdimm {int /*<<< orphan*/  dwork; int /*<<< orphan*/  flags; TYPE_1__ sec; } ;
struct device {scalar_t__ class; } ;

/* Variables and functions */
 int /*<<< orphan*/  NDD_WORK_PENDING ; 
 int /*<<< orphan*/  ND_SYNC ; 
 int /*<<< orphan*/  NVDIMM_SECURITY_FROZEN ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ is_nvdimm (struct device*) ; 
 int /*<<< orphan*/  nd_device_unregister (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nvdimm* to_nvdimm (struct device*) ; 

__attribute__((used)) static int child_unregister(struct device *dev, void *data)
{
	/*
	 * the singular ndctl class device per bus needs to be
	 * "device_destroy"ed, so skip it here
	 *
	 * i.e. remove classless children
	 */
	if (dev->class)
		return 0;

	if (is_nvdimm(dev)) {
		struct nvdimm *nvdimm = to_nvdimm(dev);
		bool dev_put = false;

		/* We are shutting down. Make state frozen artificially. */
		nvdimm_bus_lock(dev);
		set_bit(NVDIMM_SECURITY_FROZEN, &nvdimm->sec.flags);
		if (test_and_clear_bit(NDD_WORK_PENDING, &nvdimm->flags))
			dev_put = true;
		nvdimm_bus_unlock(dev);
		cancel_delayed_work_sync(&nvdimm->dwork);
		if (dev_put)
			put_device(dev);
	}
	nd_device_unregister(dev, ND_SYNC);

	return 0;
}