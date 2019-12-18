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
struct vfio_group {int dummy; } ;
struct notifier_block {int dummy; } ;
struct device {int dummy; } ;
typedef  enum vfio_notify_type { ____Placeholder_vfio_notify_type } vfio_notify_type ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
#define  VFIO_GROUP_NOTIFY 129 
#define  VFIO_IOMMU_NOTIFY 128 
 struct vfio_group* vfio_group_get_from_dev (struct device*) ; 
 int /*<<< orphan*/  vfio_group_put (struct vfio_group*) ; 
 int vfio_register_group_notifier (struct vfio_group*,unsigned long*,struct notifier_block*) ; 
 int vfio_register_iommu_notifier (struct vfio_group*,unsigned long*,struct notifier_block*) ; 

int vfio_register_notifier(struct device *dev, enum vfio_notify_type type,
			   unsigned long *events, struct notifier_block *nb)
{
	struct vfio_group *group;
	int ret;

	if (!dev || !nb || !events || (*events == 0))
		return -EINVAL;

	group = vfio_group_get_from_dev(dev);
	if (!group)
		return -ENODEV;

	switch (type) {
	case VFIO_IOMMU_NOTIFY:
		ret = vfio_register_iommu_notifier(group, events, nb);
		break;
	case VFIO_GROUP_NOTIFY:
		ret = vfio_register_group_notifier(group, events, nb);
		break;
	default:
		ret = -EINVAL;
	}

	vfio_group_put(group);
	return ret;
}