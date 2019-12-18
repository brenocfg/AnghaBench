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
struct mdev_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {unsigned long aqm_max; int /*<<< orphan*/  aqm; } ;
struct ap_matrix_mdev {TYPE_1__ matrix; scalar_t__ kvm; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  clear_bit_inv (unsigned long,int /*<<< orphan*/ ) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 TYPE_2__* matrix_dev ; 
 struct mdev_device* mdev_from_dev (struct device*) ; 
 struct ap_matrix_mdev* mdev_get_drvdata (struct mdev_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit_inv (unsigned long,int /*<<< orphan*/ ) ; 
 int vfio_ap_mdev_verify_no_sharing (struct ap_matrix_mdev*) ; 
 int vfio_ap_mdev_verify_queues_reserved_for_apqi (struct ap_matrix_mdev*,unsigned long) ; 

__attribute__((used)) static ssize_t assign_domain_store(struct device *dev,
				   struct device_attribute *attr,
				   const char *buf, size_t count)
{
	int ret;
	unsigned long apqi;
	struct mdev_device *mdev = mdev_from_dev(dev);
	struct ap_matrix_mdev *matrix_mdev = mdev_get_drvdata(mdev);
	unsigned long max_apqi = matrix_mdev->matrix.aqm_max;

	/* If the guest is running, disallow assignment of domain */
	if (matrix_mdev->kvm)
		return -EBUSY;

	ret = kstrtoul(buf, 0, &apqi);
	if (ret)
		return ret;
	if (apqi > max_apqi)
		return -ENODEV;

	mutex_lock(&matrix_dev->lock);

	ret = vfio_ap_mdev_verify_queues_reserved_for_apqi(matrix_mdev, apqi);
	if (ret)
		goto done;

	set_bit_inv(apqi, matrix_mdev->matrix.aqm);

	ret = vfio_ap_mdev_verify_no_sharing(matrix_mdev);
	if (ret)
		goto share_err;

	ret = count;
	goto done;

share_err:
	clear_bit_inv(apqi, matrix_mdev->matrix.aqm);
done:
	mutex_unlock(&matrix_dev->lock);

	return ret;
}