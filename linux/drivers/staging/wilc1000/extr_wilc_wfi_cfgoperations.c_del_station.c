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
typedef  int /*<<< orphan*/  u8 ;
struct wiphy {int dummy; } ;
struct sta_info {int /*<<< orphan*/  sta_associated_bss; } ;
struct wilc_priv {struct sta_info assoc_stainfo; } ;
struct wilc_vif {scalar_t__ iftype; struct wilc_priv priv; } ;
struct station_del_parameters {int /*<<< orphan*/ * mac; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ WILC_AP_MODE ; 
 scalar_t__ WILC_GO_MODE ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int wilc_del_allstation (struct wilc_vif*,int /*<<< orphan*/ ) ; 
 int wilc_del_station (struct wilc_vif*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int del_station(struct wiphy *wiphy, struct net_device *dev,
		       struct station_del_parameters *params)
{
	const u8 *mac = params->mac;
	int ret = 0;
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc_priv *priv = &vif->priv;
	struct sta_info *info;

	if (!(vif->iftype == WILC_AP_MODE || vif->iftype == WILC_GO_MODE))
		return ret;

	info = &priv->assoc_stainfo;

	if (!mac)
		ret = wilc_del_allstation(vif, info->sta_associated_bss);

	ret = wilc_del_station(vif, mac);
	if (ret)
		netdev_err(dev, "Host delete station fail\n");
	return ret;
}