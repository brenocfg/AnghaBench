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
struct phy {scalar_t__ init_count; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* init ) (struct phy*) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int phy_pm_runtime_get_sync (struct phy*) ; 
 int /*<<< orphan*/  phy_pm_runtime_put (struct phy*) ; 
 int stub1 (struct phy*) ; 

int phy_init(struct phy *phy)
{
	int ret;

	if (!phy)
		return 0;

	ret = phy_pm_runtime_get_sync(phy);
	if (ret < 0 && ret != -ENOTSUPP)
		return ret;
	ret = 0; /* Override possible ret == -ENOTSUPP */

	mutex_lock(&phy->mutex);
	if (phy->init_count == 0 && phy->ops->init) {
		ret = phy->ops->init(phy);
		if (ret < 0) {
			dev_err(&phy->dev, "phy init failed --> %d\n", ret);
			goto out;
		}
	}
	++phy->init_count;

out:
	mutex_unlock(&phy->mutex);
	phy_pm_runtime_put(phy);
	return ret;
}