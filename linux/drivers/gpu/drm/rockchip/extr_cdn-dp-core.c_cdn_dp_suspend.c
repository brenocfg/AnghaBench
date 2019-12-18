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
struct cdn_dp_device {int suspended; int /*<<< orphan*/  lock; scalar_t__ active; } ;

/* Variables and functions */
 int cdn_dp_disable (struct cdn_dp_device*) ; 
 struct cdn_dp_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int cdn_dp_suspend(struct device *dev)
{
	struct cdn_dp_device *dp = dev_get_drvdata(dev);
	int ret = 0;

	mutex_lock(&dp->lock);
	if (dp->active)
		ret = cdn_dp_disable(dp);
	dp->suspended = true;
	mutex_unlock(&dp->lock);

	return ret;
}