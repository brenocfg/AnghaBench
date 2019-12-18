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
struct iommu_param {int /*<<< orphan*/  lock; struct iommu_fault_param* fault_param; } ;
struct iommu_fault_param {int (* handler ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  data; int /*<<< orphan*/  faults; } ;
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {scalar_t__ type; TYPE_1__ prm; } ;
struct iommu_fault_event {int /*<<< orphan*/  list; TYPE_2__ fault; } ;
struct device {struct iommu_param* iommu_param; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IOMMU_FAULT_PAGE_REQ ; 
 int IOMMU_FAULT_PAGE_REQUEST_LAST_PAGE ; 
 int /*<<< orphan*/  kfree (struct iommu_fault_event*) ; 
 struct iommu_fault_event* kmemdup (struct iommu_fault_event*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

int iommu_report_device_fault(struct device *dev, struct iommu_fault_event *evt)
{
	struct iommu_param *param = dev->iommu_param;
	struct iommu_fault_event *evt_pending = NULL;
	struct iommu_fault_param *fparam;
	int ret = 0;

	if (!param || !evt)
		return -EINVAL;

	/* we only report device fault if there is a handler registered */
	mutex_lock(&param->lock);
	fparam = param->fault_param;
	if (!fparam || !fparam->handler) {
		ret = -EINVAL;
		goto done_unlock;
	}

	if (evt->fault.type == IOMMU_FAULT_PAGE_REQ &&
	    (evt->fault.prm.flags & IOMMU_FAULT_PAGE_REQUEST_LAST_PAGE)) {
		evt_pending = kmemdup(evt, sizeof(struct iommu_fault_event),
				      GFP_KERNEL);
		if (!evt_pending) {
			ret = -ENOMEM;
			goto done_unlock;
		}
		mutex_lock(&fparam->lock);
		list_add_tail(&evt_pending->list, &fparam->faults);
		mutex_unlock(&fparam->lock);
	}

	ret = fparam->handler(&evt->fault, fparam->data);
	if (ret && evt_pending) {
		mutex_lock(&fparam->lock);
		list_del(&evt_pending->list);
		mutex_unlock(&fparam->lock);
		kfree(evt_pending);
	}
done_unlock:
	mutex_unlock(&param->lock);
	return ret;
}