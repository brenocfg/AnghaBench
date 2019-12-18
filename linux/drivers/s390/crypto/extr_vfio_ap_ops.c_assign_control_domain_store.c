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
struct TYPE_3__ {unsigned long adm_max; int /*<<< orphan*/  adm; } ;
struct ap_matrix_mdev {TYPE_1__ matrix; scalar_t__ kvm; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 TYPE_2__* matrix_dev ; 
 struct mdev_device* mdev_from_dev (struct device*) ; 
 struct ap_matrix_mdev* mdev_get_drvdata (struct mdev_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit_inv (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t assign_control_domain_store(struct device *dev,
					   struct device_attribute *attr,
					   const char *buf, size_t count)
{
	int ret;
	unsigned long id;
	struct mdev_device *mdev = mdev_from_dev(dev);
	struct ap_matrix_mdev *matrix_mdev = mdev_get_drvdata(mdev);

	/* If the guest is running, disallow assignment of control domain */
	if (matrix_mdev->kvm)
		return -EBUSY;

	ret = kstrtoul(buf, 0, &id);
	if (ret)
		return ret;

	if (id > matrix_mdev->matrix.adm_max)
		return -ENODEV;

	/* Set the bit in the ADM (bitmask) corresponding to the AP control
	 * domain number (id). The bits in the mask, from most significant to
	 * least significant, correspond to IDs 0 up to the one less than the
	 * number of control domains that can be assigned.
	 */
	mutex_lock(&matrix_dev->lock);
	set_bit_inv(id, matrix_mdev->matrix.adm);
	mutex_unlock(&matrix_dev->lock);

	return count;
}