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
struct phy {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  pm_runtime_enabled (int /*<<< orphan*/ *) ; 
 int pm_runtime_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 

int phy_pm_runtime_get(struct phy *phy)
{
	int ret;

	if (!phy)
		return 0;

	if (!pm_runtime_enabled(&phy->dev))
		return -ENOTSUPP;

	ret = pm_runtime_get(&phy->dev);
	if (ret < 0 && ret != -EINPROGRESS)
		pm_runtime_put_noidle(&phy->dev);

	return ret;
}