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
typedef  int /*<<< orphan*/  iommu_dev_fault_handler_t ;
struct TYPE_2__ {int /*<<< orphan*/  faults; int /*<<< orphan*/  lock; void* data; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

int iommu_register_device_fault_handler(struct device *dev,
					iommu_dev_fault_handler_t handler,
					void *data)
{
	struct iommu_param *param = dev->iommu_param;
	int ret = 0;

	if (!param)
		return -EINVAL;

	mutex_lock(&param->lock);
	/* Only allow one fault handler registered for each device */
	if (param->fault_param) {
		ret = -EBUSY;
		goto done_unlock;
	}

	get_device(dev);
	param->fault_param = kzalloc(sizeof(*param->fault_param), GFP_KERNEL);
	if (!param->fault_param) {
		put_device(dev);
		ret = -ENOMEM;
		goto done_unlock;
	}
	param->fault_param->handler = handler;
	param->fault_param->data = data;
	mutex_init(&param->fault_param->lock);
	INIT_LIST_HEAD(&param->fault_param->faults);

done_unlock:
	mutex_unlock(&param->lock);

	return ret;
}