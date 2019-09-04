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
struct file {int dummy; } ;
struct adf_user_cfg_ctl_data {int /*<<< orphan*/  device_id; } ;
struct adf_accel_dev {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADF_STATUS_CONFIGURED ; 
 int EFAULT ; 
 scalar_t__ adf_copy_key_value_data (struct adf_accel_dev*,struct adf_user_cfg_ctl_data*) ; 
 int adf_ctl_alloc_resources (struct adf_user_cfg_ctl_data**,unsigned long) ; 
 scalar_t__ adf_dev_started (struct adf_accel_dev*) ; 
 struct adf_accel_dev* adf_devmgr_get_dev_by_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct adf_user_cfg_ctl_data*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adf_ctl_ioctl_dev_config(struct file *fp, unsigned int cmd,
				    unsigned long arg)
{
	int ret;
	struct adf_user_cfg_ctl_data *ctl_data;
	struct adf_accel_dev *accel_dev;

	ret = adf_ctl_alloc_resources(&ctl_data, arg);
	if (ret)
		return ret;

	accel_dev = adf_devmgr_get_dev_by_id(ctl_data->device_id);
	if (!accel_dev) {
		ret = -EFAULT;
		goto out;
	}

	if (adf_dev_started(accel_dev)) {
		ret = -EFAULT;
		goto out;
	}

	if (adf_copy_key_value_data(accel_dev, ctl_data)) {
		ret = -EFAULT;
		goto out;
	}
	set_bit(ADF_STATUS_CONFIGURED, &accel_dev->status);
out:
	kfree(ctl_data);
	return ret;
}