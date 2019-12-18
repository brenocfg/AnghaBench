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
struct notifier_block {int dummy; } ;
struct iommu_group {int /*<<< orphan*/  notifier; } ;
struct device {int dummy; } ;

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
 int iommu_probe_device (struct device*) ; 
 int /*<<< orphan*/  iommu_release_device (struct device*) ; 

__attribute__((used)) static int iommu_bus_notifier(struct notifier_block *nb,
			      unsigned long action, void *data)
{
	unsigned long group_action = 0;
	struct device *dev = data;
	struct iommu_group *group;

	/*
	 * ADD/DEL call into iommu driver ops if provided, which may
	 * result in ADD/DEL notifiers to group->notifier
	 */
	if (action == BUS_NOTIFY_ADD_DEVICE) {
		int ret;

		ret = iommu_probe_device(dev);
		return (ret) ? NOTIFY_DONE : NOTIFY_OK;
	} else if (action == BUS_NOTIFY_REMOVED_DEVICE) {
		iommu_release_device(dev);
		return NOTIFY_OK;
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