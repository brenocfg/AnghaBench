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
struct phy {int /*<<< orphan*/  mutex; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* reset ) (struct phy*) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int phy_pm_runtime_get_sync (struct phy*) ; 
 int /*<<< orphan*/  phy_pm_runtime_put (struct phy*) ; 
 int stub1 (struct phy*) ; 

int phy_reset(struct phy *phy)
{
	int ret;

	if (!phy || !phy->ops->reset)
		return 0;

	ret = phy_pm_runtime_get_sync(phy);
	if (ret < 0 && ret != -ENOTSUPP)
		return ret;

	mutex_lock(&phy->mutex);
	ret = phy->ops->reset(phy);
	mutex_unlock(&phy->mutex);

	phy_pm_runtime_put(phy);

	return ret;
}