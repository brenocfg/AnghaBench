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
struct hl_device {scalar_t__ pm_mng_profile; int /*<<< orphan*/  fpriv_list_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  work_freq; int /*<<< orphan*/  curr_pll_profile; scalar_t__ compute_ctx; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ENODEV ; 
 size_t EPERM ; 
 int /*<<< orphan*/  PLL_HIGH ; 
 int /*<<< orphan*/  PLL_LOW ; 
 scalar_t__ PM_AUTO ; 
 scalar_t__ PM_MANUAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct hl_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 scalar_t__ hl_device_disabled_or_in_reset (struct hl_device*) ; 
 int /*<<< orphan*/  hl_device_set_frequency (struct hl_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t pm_mng_profile_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct hl_device *hdev = dev_get_drvdata(dev);

	if (hl_device_disabled_or_in_reset(hdev)) {
		count = -ENODEV;
		goto out;
	}

	mutex_lock(&hdev->fpriv_list_lock);

	if (hdev->compute_ctx) {
		dev_err(hdev->dev,
			"Can't change PM profile while compute context is opened on the device\n");
		count = -EPERM;
		goto unlock_mutex;
	}

	if (strncmp("auto", buf, strlen("auto")) == 0) {
		/* Make sure we are in LOW PLL when changing modes */
		if (hdev->pm_mng_profile == PM_MANUAL) {
			hdev->curr_pll_profile = PLL_HIGH;
			hl_device_set_frequency(hdev, PLL_LOW);
			hdev->pm_mng_profile = PM_AUTO;
		}
	} else if (strncmp("manual", buf, strlen("manual")) == 0) {
		if (hdev->pm_mng_profile == PM_AUTO) {
			/* Must release the lock because the work thread also
			 * takes this lock. But before we release it, set
			 * the mode to manual so nothing will change if a user
			 * suddenly opens the device
			 */
			hdev->pm_mng_profile = PM_MANUAL;

			mutex_unlock(&hdev->fpriv_list_lock);

			/* Flush the current work so we can return to the user
			 * knowing that he is the only one changing frequencies
			 */
			flush_delayed_work(&hdev->work_freq);

			return count;
		}
	} else {
		dev_err(hdev->dev, "value should be auto or manual\n");
		count = -EINVAL;
	}

unlock_mutex:
	mutex_unlock(&hdev->fpriv_list_lock);
out:
	return count;
}