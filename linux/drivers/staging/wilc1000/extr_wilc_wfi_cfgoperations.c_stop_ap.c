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
struct wilc_vif {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WILC_AP_MODE ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int wilc_del_beacon (struct wilc_vif*) ; 
 int /*<<< orphan*/  wilc_wlan_set_bssid (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stop_ap(struct wiphy *wiphy, struct net_device *dev)
{
	int ret;
	struct wilc_vif *vif = netdev_priv(dev);

	wilc_wlan_set_bssid(dev, NULL, WILC_AP_MODE);

	ret = wilc_del_beacon(vif);

	if (ret)
		netdev_err(dev, "Host delete beacon fail\n");

	return ret;
}