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
struct mdev_device {int dummy; } ;
struct ap_matrix_mdev {int /*<<< orphan*/  node; scalar_t__ kvm; } ;
struct TYPE_2__ {int /*<<< orphan*/  available_instances; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ap_matrix_mdev*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 TYPE_1__* matrix_dev ; 
 struct ap_matrix_mdev* mdev_get_drvdata (struct mdev_device*) ; 
 int /*<<< orphan*/  mdev_set_drvdata (struct mdev_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfio_ap_mdev_reset_queues (struct mdev_device*) ; 

__attribute__((used)) static int vfio_ap_mdev_remove(struct mdev_device *mdev)
{
	struct ap_matrix_mdev *matrix_mdev = mdev_get_drvdata(mdev);

	if (matrix_mdev->kvm)
		return -EBUSY;

	mutex_lock(&matrix_dev->lock);
	vfio_ap_mdev_reset_queues(mdev);
	list_del(&matrix_mdev->node);
	mutex_unlock(&matrix_dev->lock);

	kfree(matrix_mdev);
	mdev_set_drvdata(mdev, NULL);
	atomic_inc(&matrix_dev->available_instances);

	return 0;
}