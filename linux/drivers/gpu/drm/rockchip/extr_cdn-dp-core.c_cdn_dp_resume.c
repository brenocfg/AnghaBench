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
struct cdn_dp_device {int suspended; int /*<<< orphan*/  lock; int /*<<< orphan*/  event_work; scalar_t__ fw_loaded; } ;

/* Variables and functions */
 struct cdn_dp_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

int cdn_dp_resume(struct device *dev)
{
	struct cdn_dp_device *dp = dev_get_drvdata(dev);

	mutex_lock(&dp->lock);
	dp->suspended = false;
	if (dp->fw_loaded)
		schedule_work(&dp->event_work);
	mutex_unlock(&dp->lock);

	return 0;
}