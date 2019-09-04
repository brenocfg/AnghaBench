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
struct notifier_block {int dummy; } ;
struct iommu_ops {int (* add_device ) (struct device*) ;int /*<<< orphan*/  (* remove_device ) (struct device*) ;} ;
struct iommu_group {int /*<<< orphan*/  notifier; } ;
struct device {scalar_t__ iommu_group; TYPE_1__* bus; } ;
struct TYPE_2__ {struct iommu_ops* iommu_ops; } ;

/* Variables and functions */
 unsigned long BUS_NOTIFY_ADD_DEVICE ; 
#define  BUS_NOTIFY_BIND_DRIVER 131 
#define  BUS_NOTIFY_BOUND_DRIVER 130 
 unsigned long BUS_NOTIFY_REMOVED_DEVICE ; 
#define  BUS_NOTIFY_UNBIND_DRIVER 129 
#define  BUS_NOTIFY_UNBOUND_DRIVER 128 
 unsigned long IOMMU_GROUP_NOTIFY_BIND_DRIVER ; 
 unsigned long IOMMU_GROUP_NOTIFY_BOUND_DRIVER ; 
 unsigned long IOMMU_GROUP_NOTIFY_UNBIND_DRIVER ; 
 unsigned long IOMMU_GROUP_NOTIFY_UNBOUND_DRIVER ; 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,unsigned long,struct device*) ; 
 struct iommu_group* iommu_group_get (struct device*) ; 
 int /*<<< orphan*/  iommu_group_put (struct iommu_group*) ; 
 int stub1 (struct device*) ; 
 int /*<<< orphan*/  stub2 (struct device*) ; 

__attribute__((used)) static int iommu_bus_notifier(struct notifier_block *nb,
			      unsigned long action, void *data)
{
	struct device *dev = data;
	const struct iommu_ops *ops = dev->bus->iommu_ops;
	struct iommu_group *group;
	unsigned long group_action = 0;

	/*
	 * ADD/DEL call into iommu driver ops if provided, which may
	 * result in ADD/DEL notifiers to group->notifier
	 */
	if (action == BUS_NOTIFY_ADD_DEVICE) {
		if (ops->add_device) {
			int ret;

			ret = ops->add_device(dev);
			return (ret) ? NOTIFY_DONE : NOTIFY_OK;
		}
	} else if (action == BUS_NOTIFY_REMOVED_DEVICE) {
		if (ops->remove_device && dev->iommu_group) {
			ops->remove_device(dev);
			return 0;
		}
	}

	/*
	 * Remaining BUS_NOTIFYs get filtered and republished to the
	 * group, if anyone is listening
	 */
	group = iommu_group_get(dev);
	if (!group)
		return 0;

	switch (action) {
	case BUS_NOTIFY_BIND_DRIVER:
		group_action = IOMMU_GROUP_NOTIFY_BIND_DRIVER;
		break;
	case BUS_NOTIFY_BOUND_DRIVER:
		group_action = IOMMU_GROUP_NOTIFY_BOUND_DRIVER;
		break;
	case BUS_NOTIFY_UNBIND_DRIVER:
		group_action = IOMMU_GROUP_NOTIFY_UNBIND_DRIVER;
		break;
	case BUS_NOTIFY_UNBOUND_DRIVER:
		group_action = IOMMU_GROUP_NOTIFY_UNBOUND_DRIVER;
		break;
	}

	if (group_action)
		blocking_notifier_call_chain(&group->notifier,
					     group_action, dev);

	iommu_group_put(group);
	return 0;
}