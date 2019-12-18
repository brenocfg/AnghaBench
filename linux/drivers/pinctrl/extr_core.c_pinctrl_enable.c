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
struct pinctrl_dev {int /*<<< orphan*/  node; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pinctrl_claim_hogs (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  pinctrl_init_device_debugfs (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  pinctrldev_list ; 
 int /*<<< orphan*/  pinctrldev_list_mutex ; 

int pinctrl_enable(struct pinctrl_dev *pctldev)
{
	int error;

	error = pinctrl_claim_hogs(pctldev);
	if (error) {
		dev_err(pctldev->dev, "could not claim hogs: %i\n",
			error);
		mutex_destroy(&pctldev->mutex);
		kfree(pctldev);

		return error;
	}

	mutex_lock(&pinctrldev_list_mutex);
	list_add_tail(&pctldev->node, &pinctrldev_list);
	mutex_unlock(&pinctrldev_list_mutex);

	pinctrl_init_device_debugfs(pctldev);

	return 0;
}