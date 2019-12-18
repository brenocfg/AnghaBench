#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mdev_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  notifier_call; } ;
struct ap_matrix_mdev {TYPE_1__ group_notifier; TYPE_1__ iommu_notifier; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  VFIO_GROUP_NOTIFY ; 
 unsigned long VFIO_GROUP_NOTIFY_SET_KVM ; 
 int /*<<< orphan*/  VFIO_IOMMU_NOTIFY ; 
 unsigned long VFIO_IOMMU_NOTIFY_DMA_UNMAP ; 
 int /*<<< orphan*/  mdev_dev (struct mdev_device*) ; 
 struct ap_matrix_mdev* mdev_get_drvdata (struct mdev_device*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_ap_mdev_group_notifier ; 
 int /*<<< orphan*/  vfio_ap_mdev_iommu_notifier ; 
 int vfio_register_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*,TYPE_1__*) ; 
 int /*<<< orphan*/  vfio_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int vfio_ap_mdev_open(struct mdev_device *mdev)
{
	struct ap_matrix_mdev *matrix_mdev = mdev_get_drvdata(mdev);
	unsigned long events;
	int ret;


	if (!try_module_get(THIS_MODULE))
		return -ENODEV;

	matrix_mdev->group_notifier.notifier_call = vfio_ap_mdev_group_notifier;
	events = VFIO_GROUP_NOTIFY_SET_KVM;

	ret = vfio_register_notifier(mdev_dev(mdev), VFIO_GROUP_NOTIFY,
				     &events, &matrix_mdev->group_notifier);
	if (ret) {
		module_put(THIS_MODULE);
		return ret;
	}

	matrix_mdev->iommu_notifier.notifier_call = vfio_ap_mdev_iommu_notifier;
	events = VFIO_IOMMU_NOTIFY_DMA_UNMAP;
	ret = vfio_register_notifier(mdev_dev(mdev), VFIO_IOMMU_NOTIFY,
				     &events, &matrix_mdev->iommu_notifier);
	if (!ret)
		return ret;

	vfio_unregister_notifier(mdev_dev(mdev), VFIO_GROUP_NOTIFY,
				 &matrix_mdev->group_notifier);
	module_put(THIS_MODULE);
	return ret;
}