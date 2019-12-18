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
struct wiphy {int dummy; } ;
struct qtnf_vif {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLINK_PM_AUTO_STANDBY ; 
 int /*<<< orphan*/  QLINK_PM_OFF ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_send_pm_set (struct qtnf_vif*,int /*<<< orphan*/ ,int) ; 
 struct qtnf_vif* qtnf_netdev_get_priv (struct net_device*) ; 

__attribute__((used)) static int qtnf_set_power_mgmt(struct wiphy *wiphy, struct net_device *dev,
			       bool enabled, int timeout)
{
	struct qtnf_vif *vif = qtnf_netdev_get_priv(dev);
	int ret;

	ret = qtnf_cmd_send_pm_set(vif, enabled ? QLINK_PM_AUTO_STANDBY :
				   QLINK_PM_OFF, timeout);
	if (ret)
		pr_err("%s: failed to set PM mode ret=%d\n", dev->name, ret);

	return ret;
}