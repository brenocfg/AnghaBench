#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mdev_device {int dummy; } ;
struct ap_matrix_mdev {int /*<<< orphan*/  group_notifier; int /*<<< orphan*/  iommu_notifier; TYPE_4__* kvm; } ;
struct TYPE_6__ {int /*<<< orphan*/ * pqap_hook; } ;
struct TYPE_7__ {TYPE_1__ crypto; } ;
struct TYPE_9__ {TYPE_2__ arch; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  VFIO_GROUP_NOTIFY ; 
 int /*<<< orphan*/  VFIO_IOMMU_NOTIFY ; 
 int /*<<< orphan*/  kvm_arch_crypto_clear_masks (TYPE_4__*) ; 
 int /*<<< orphan*/  kvm_put_kvm (TYPE_4__*) ; 
 TYPE_3__* matrix_dev ; 
 int /*<<< orphan*/  mdev_dev (struct mdev_device*) ; 
 struct ap_matrix_mdev* mdev_get_drvdata (struct mdev_device*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfio_ap_mdev_reset_queues (struct mdev_device*) ; 
 int /*<<< orphan*/  vfio_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vfio_ap_mdev_release(struct mdev_device *mdev)
{
	struct ap_matrix_mdev *matrix_mdev = mdev_get_drvdata(mdev);

	mutex_lock(&matrix_dev->lock);
	if (matrix_mdev->kvm) {
		kvm_arch_crypto_clear_masks(matrix_mdev->kvm);
		matrix_mdev->kvm->arch.crypto.pqap_hook = NULL;
		vfio_ap_mdev_reset_queues(mdev);
		kvm_put_kvm(matrix_mdev->kvm);
		matrix_mdev->kvm = NULL;
	}
	mutex_unlock(&matrix_dev->lock);

	vfio_unregister_notifier(mdev_dev(mdev), VFIO_IOMMU_NOTIFY,
				 &matrix_mdev->iommu_notifier);
	vfio_unregister_notifier(mdev_dev(mdev), VFIO_GROUP_NOTIFY,
				 &matrix_mdev->group_notifier);
	module_put(THIS_MODULE);
}