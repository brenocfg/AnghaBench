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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct cfg80211_ap_settings {int /*<<< orphan*/  beacon; int /*<<< orphan*/  dtim_period; int /*<<< orphan*/  beacon_interval; int /*<<< orphan*/  chandef; } ;

/* Variables and functions */
 int /*<<< orphan*/  WILC_AP_MODE ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int set_channel (struct wiphy*,int /*<<< orphan*/ *) ; 
 int wilc_add_beacon (struct wilc_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wilc_wlan_set_bssid (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_ap(struct wiphy *wiphy, struct net_device *dev,
		    struct cfg80211_ap_settings *settings)
{
	struct wilc_vif *vif = netdev_priv(dev);
	int ret;

	ret = set_channel(wiphy, &settings->chandef);
	if (ret != 0)
		netdev_err(dev, "Error in setting channel\n");

	wilc_wlan_set_bssid(dev, dev->dev_addr, WILC_AP_MODE);

	return wilc_add_beacon(vif, settings->beacon_interval,
				   settings->dtim_period, &settings->beacon);
}