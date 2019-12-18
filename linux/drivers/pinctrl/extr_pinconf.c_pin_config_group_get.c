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
struct pinctrl_dev {int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; TYPE_1__* desc; } ;
struct pinconf_ops {int (* pin_config_group_get ) (struct pinctrl_dev*,int,unsigned long*) ;} ;
struct TYPE_2__ {struct pinconf_ops* confops; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct pinctrl_dev* get_pinctrl_dev_from_devname (char const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pinctrl_get_group_selector (struct pinctrl_dev*,char const*) ; 
 int stub1 (struct pinctrl_dev*,int,unsigned long*) ; 

int pin_config_group_get(const char *dev_name, const char *pin_group,
			 unsigned long *config)
{
	struct pinctrl_dev *pctldev;
	const struct pinconf_ops *ops;
	int selector, ret;

	pctldev = get_pinctrl_dev_from_devname(dev_name);
	if (!pctldev) {
		ret = -EINVAL;
		return ret;
	}

	mutex_lock(&pctldev->mutex);

	ops = pctldev->desc->confops;

	if (!ops || !ops->pin_config_group_get) {
		dev_dbg(pctldev->dev,
			"cannot get configuration for pin group, missing group config get function in driver\n");
		ret = -ENOTSUPP;
		goto unlock;
	}

	selector = pinctrl_get_group_selector(pctldev, pin_group);
	if (selector < 0) {
		ret = selector;
		goto unlock;
	}

	ret = ops->pin_config_group_get(pctldev, selector, config);

unlock:
	mutex_unlock(&pctldev->mutex);
	return ret;
}