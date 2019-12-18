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
typedef  int /*<<< orphan*/  u8 ;
struct wiphy {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  associated_bss; } ;
struct wilc_vif {TYPE_1__ priv; } ;
struct station_info {int /*<<< orphan*/  signal; int /*<<< orphan*/  filled; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  NL80211_STA_INFO_SIGNAL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int wilc_get_rssi (struct wilc_vif*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dump_station(struct wiphy *wiphy, struct net_device *dev,
			int idx, u8 *mac, struct station_info *sinfo)
{
	struct wilc_vif *vif = netdev_priv(dev);
	int ret;

	if (idx != 0)
		return -ENOENT;

	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL);

	ret = wilc_get_rssi(vif, &sinfo->signal);
	if (ret)
		return ret;

	memcpy(mac, vif->priv.associated_bss, ETH_ALEN);
	return 0;
}