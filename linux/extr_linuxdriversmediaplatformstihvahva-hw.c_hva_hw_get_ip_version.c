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
struct hva_dev {scalar_t__ regs; int /*<<< orphan*/  protect_mutex; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned long EFAULT ; 
 scalar_t__ HVA_HIF_REG_VERSION ; 
 int /*<<< orphan*/  HVA_PREFIX ; 
 unsigned long HVA_VERSION_UNKNOWN ; 
#define  HVA_VERSION_V400 128 
 unsigned long VERSION_ID_MASK ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 struct device* hva_to_dev (struct hva_dev*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (struct device*) ; 
 unsigned long readl_relaxed (scalar_t__) ; 

__attribute__((used)) static unsigned long int hva_hw_get_ip_version(struct hva_dev *hva)
{
	struct device *dev = hva_to_dev(hva);
	unsigned long int version;

	if (pm_runtime_get_sync(dev) < 0) {
		dev_err(dev, "%s     failed to get pm_runtime\n", HVA_PREFIX);
		mutex_unlock(&hva->protect_mutex);
		return -EFAULT;
	}

	version = readl_relaxed(hva->regs + HVA_HIF_REG_VERSION) &
				VERSION_ID_MASK;

	pm_runtime_put_autosuspend(dev);

	switch (version) {
	case HVA_VERSION_V400:
		dev_dbg(dev, "%s     IP hardware version 0x%lx\n",
			HVA_PREFIX, version);
		break;
	default:
		dev_err(dev, "%s     unknown IP hardware version 0x%lx\n",
			HVA_PREFIX, version);
		version = HVA_VERSION_UNKNOWN;
		break;
	}

	return version;
}