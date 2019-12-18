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
struct iommu_param {int /*<<< orphan*/  lock; TYPE_1__* fault_param; } ;
struct device {struct iommu_param* iommu_param; } ;
struct TYPE_2__ {int /*<<< orphan*/  faults; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

int iommu_unregister_device_fault_handler(struct device *dev)
{
	struct iommu_param *param = dev->iommu_param;
	int ret = 0;

	if (!param)
		return -EINVAL;

	mutex_lock(&param->lock);

	if (!param->fault_param)
		goto unlock;

	/* we cannot unregister handler if there are pending faults */
	if (!list_empty(&param->fault_param->faults)) {
		ret = -EBUSY;
		goto unlock;
	}

	kfree(param->fault_param);
	param->fault_param = NULL;
	put_device(dev);
unlock:
	mutex_unlock(&param->lock);

	return ret;
}