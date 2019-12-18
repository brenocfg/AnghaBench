#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct wiphy {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * sta_associated_bss; } ;
struct wilc_priv {TYPE_1__ assoc_stainfo; } ;
struct wilc_vif {scalar_t__ iftype; struct wilc_priv priv; } ;
struct TYPE_4__ {int legacy; } ;
struct station_info {int filled; int inactive_time; TYPE_2__ txrate; scalar_t__ tx_failed; scalar_t__ tx_packets; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  signal; } ;
struct rf_info {int link_speed; scalar_t__ tx_fail_cnt; scalar_t__ tx_cnt; int /*<<< orphan*/  rx_cnt; int /*<<< orphan*/  rssi; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int BIT_ULL (int /*<<< orphan*/ ) ; 
 int DEFAULT_LINK_SPEED ; 
 int ENOENT ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  NL80211_STA_INFO_INACTIVE_TIME ; 
 int /*<<< orphan*/  NL80211_STA_INFO_RX_PACKETS ; 
 int /*<<< orphan*/  NL80211_STA_INFO_SIGNAL ; 
 int /*<<< orphan*/  NL80211_STA_INFO_TX_BITRATE ; 
 int /*<<< orphan*/  NL80211_STA_INFO_TX_FAILED ; 
 int /*<<< orphan*/  NL80211_STA_INFO_TX_PACKETS ; 
 size_t NUM_STA_ASSOCIATED ; 
 int TCP_ACK_FILTER_LINK_SPEED_THRESH ; 
 scalar_t__ WILC_AP_MODE ; 
 scalar_t__ WILC_GO_MODE ; 
 scalar_t__ WILC_STATION_MODE ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  wilc_enable_tcp_ack_filter (struct wilc_vif*,int) ; 
 int /*<<< orphan*/  wilc_get_inactive_time (struct wilc_vif*,int /*<<< orphan*/  const*,size_t*) ; 
 int /*<<< orphan*/  wilc_get_statistics (struct wilc_vif*,struct rf_info*) ; 

__attribute__((used)) static int get_station(struct wiphy *wiphy, struct net_device *dev,
		       const u8 *mac, struct station_info *sinfo)
{
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc_priv *priv = &vif->priv;
	u32 i = 0;
	u32 associatedsta = ~0;
	u32 inactive_time = 0;

	if (vif->iftype == WILC_AP_MODE || vif->iftype == WILC_GO_MODE) {
		for (i = 0; i < NUM_STA_ASSOCIATED; i++) {
			if (!(memcmp(mac,
				     priv->assoc_stainfo.sta_associated_bss[i],
				     ETH_ALEN))) {
				associatedsta = i;
				break;
			}
		}

		if (associatedsta == ~0) {
			netdev_err(dev, "sta required is not associated\n");
			return -ENOENT;
		}

		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_INACTIVE_TIME);

		wilc_get_inactive_time(vif, mac, &inactive_time);
		sinfo->inactive_time = 1000 * inactive_time;
	} else if (vif->iftype == WILC_STATION_MODE) {
		struct rf_info stats;

		wilc_get_statistics(vif, &stats);

		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL) |
				 BIT_ULL(NL80211_STA_INFO_RX_PACKETS) |
				 BIT_ULL(NL80211_STA_INFO_TX_PACKETS) |
				 BIT_ULL(NL80211_STA_INFO_TX_FAILED) |
				 BIT_ULL(NL80211_STA_INFO_TX_BITRATE);

		sinfo->signal = stats.rssi;
		sinfo->rx_packets = stats.rx_cnt;
		sinfo->tx_packets = stats.tx_cnt + stats.tx_fail_cnt;
		sinfo->tx_failed = stats.tx_fail_cnt;
		sinfo->txrate.legacy = stats.link_speed * 10;

		if (stats.link_speed > TCP_ACK_FILTER_LINK_SPEED_THRESH &&
		    stats.link_speed != DEFAULT_LINK_SPEED)
			wilc_enable_tcp_ack_filter(vif, true);
		else if (stats.link_speed != DEFAULT_LINK_SPEED)
			wilc_enable_tcp_ack_filter(vif, false);
	}
	return 0;
}