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
struct station_info {int dummy; } ;
struct net_device {int dummy; } ;
struct mwifiex_private {int /*<<< orphan*/  cfg_bssid; int /*<<< orphan*/  media_connected; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mwifiex_dump_station_info (struct mwifiex_private*,int /*<<< orphan*/ *,struct station_info*) ; 
 struct mwifiex_private* mwifiex_netdev_get_priv (struct net_device*) ; 

__attribute__((used)) static int
mwifiex_cfg80211_get_station(struct wiphy *wiphy, struct net_device *dev,
			     const u8 *mac, struct station_info *sinfo)
{
	struct mwifiex_private *priv = mwifiex_netdev_get_priv(dev);

	if (!priv->media_connected)
		return -ENOENT;
	if (memcmp(mac, priv->cfg_bssid, ETH_ALEN))
		return -ENOENT;

	return mwifiex_dump_station_info(priv, NULL, sinfo);
}