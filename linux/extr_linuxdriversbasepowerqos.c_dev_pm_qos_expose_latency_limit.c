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
struct TYPE_3__ {TYPE_2__* qos; } ;
struct device {TYPE_1__ power; } ;
struct dev_pm_qos_request {int dummy; } ;
typedef  scalar_t__ s32 ;
struct TYPE_4__ {struct dev_pm_qos_request* resume_latency_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_PM_QOS_RESUME_LATENCY ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR_OR_NULL (TYPE_2__*) ; 
 int /*<<< orphan*/  __dev_pm_qos_remove_request (struct dev_pm_qos_request*) ; 
 int dev_pm_qos_add_request (struct device*,struct dev_pm_qos_request*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_pm_qos_drop_user_request (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_qos_mtx ; 
 int /*<<< orphan*/  dev_pm_qos_sysfs_mtx ; 
 int /*<<< orphan*/  device_is_registered (struct device*) ; 
 int /*<<< orphan*/  kfree (struct dev_pm_qos_request*) ; 
 struct dev_pm_qos_request* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_qos_sysfs_add_resume_latency (struct device*) ; 

int dev_pm_qos_expose_latency_limit(struct device *dev, s32 value)
{
	struct dev_pm_qos_request *req;
	int ret;

	if (!device_is_registered(dev) || value < 0)
		return -EINVAL;

	req = kzalloc(sizeof(*req), GFP_KERNEL);
	if (!req)
		return -ENOMEM;

	ret = dev_pm_qos_add_request(dev, req, DEV_PM_QOS_RESUME_LATENCY, value);
	if (ret < 0) {
		kfree(req);
		return ret;
	}

	mutex_lock(&dev_pm_qos_sysfs_mtx);

	mutex_lock(&dev_pm_qos_mtx);

	if (IS_ERR_OR_NULL(dev->power.qos))
		ret = -ENODEV;
	else if (dev->power.qos->resume_latency_req)
		ret = -EEXIST;

	if (ret < 0) {
		__dev_pm_qos_remove_request(req);
		kfree(req);
		mutex_unlock(&dev_pm_qos_mtx);
		goto out;
	}
	dev->power.qos->resume_latency_req = req;

	mutex_unlock(&dev_pm_qos_mtx);

	ret = pm_qos_sysfs_add_resume_latency(dev);
	if (ret)
		dev_pm_qos_drop_user_request(dev, DEV_PM_QOS_RESUME_LATENCY);

 out:
	mutex_unlock(&dev_pm_qos_sysfs_mtx);
	return ret;
}