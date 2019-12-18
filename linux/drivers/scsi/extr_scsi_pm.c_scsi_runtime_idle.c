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
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  pm_runtime_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 scalar_t__ scsi_is_sdev_device (struct device*) ; 

__attribute__((used)) static int scsi_runtime_idle(struct device *dev)
{
	dev_dbg(dev, "scsi_runtime_idle\n");

	/* Insert hooks here for targets, hosts, and transport classes */

	if (scsi_is_sdev_device(dev)) {
		pm_runtime_mark_last_busy(dev);
		pm_runtime_autosuspend(dev);
		return -EBUSY;
	}

	return 0;
}