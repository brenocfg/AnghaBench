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

/* Variables and functions */
 long EFAULT ; 
#define  IOCTL_CONFIG_SYS_RESOURCE_PARAMETERS 132 
#define  IOCTL_GET_NUM_DEVICES 131 
#define  IOCTL_START_ACCEL_DEV 130 
#define  IOCTL_STATUS_ACCEL_DEV 129 
#define  IOCTL_STOP_ACCEL_DEV 128 
 int adf_ctl_ioctl_dev_config (struct file*,unsigned int,unsigned long) ; 
 int adf_ctl_ioctl_dev_start (struct file*,unsigned int,unsigned long) ; 
 int adf_ctl_ioctl_dev_stop (struct file*,unsigned int,unsigned long) ; 
 int adf_ctl_ioctl_get_num_devices (struct file*,unsigned int,unsigned long) ; 
 int adf_ctl_ioctl_get_status (struct file*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  adf_ctl_lock ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static long adf_ctl_ioctl(struct file *fp, unsigned int cmd, unsigned long arg)
{
	int ret;

	if (mutex_lock_interruptible(&adf_ctl_lock))
		return -EFAULT;

	switch (cmd) {
	case IOCTL_CONFIG_SYS_RESOURCE_PARAMETERS:
		ret = adf_ctl_ioctl_dev_config(fp, cmd, arg);
		break;

	case IOCTL_STOP_ACCEL_DEV:
		ret = adf_ctl_ioctl_dev_stop(fp, cmd, arg);
		break;

	case IOCTL_START_ACCEL_DEV:
		ret = adf_ctl_ioctl_dev_start(fp, cmd, arg);
		break;

	case IOCTL_GET_NUM_DEVICES:
		ret = adf_ctl_ioctl_get_num_devices(fp, cmd, arg);
		break;

	case IOCTL_STATUS_ACCEL_DEV:
		ret = adf_ctl_ioctl_get_status(fp, cmd, arg);
		break;
	default:
		pr_err("QAT: Invalid ioctl\n");
		ret = -EFAULT;
		break;
	}
	mutex_unlock(&adf_ctl_lock);
	return ret;
}