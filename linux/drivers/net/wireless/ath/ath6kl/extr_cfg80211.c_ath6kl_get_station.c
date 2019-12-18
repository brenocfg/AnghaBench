#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct wiphy {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  beacon_interval; int /*<<< orphan*/  dtim_period; scalar_t__ flags; } ;
struct TYPE_5__ {int legacy; int /*<<< orphan*/  flags; int /*<<< orphan*/  bw; void* mcs; } ;
struct station_info {TYPE_3__ bss_param; int /*<<< orphan*/  filled; TYPE_2__ txrate; int /*<<< orphan*/  signal; int /*<<< orphan*/  tx_packets; scalar_t__ tx_bytes; int /*<<< orphan*/  rx_packets; scalar_t__ rx_bytes; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int tx_ucast_rate; int /*<<< orphan*/  cs_rssi; int /*<<< orphan*/  tx_pkt; scalar_t__ tx_byte; int /*<<< orphan*/  rx_pkt; scalar_t__ rx_byte; } ;
struct ath6kl_vif {scalar_t__ nw_type; int /*<<< orphan*/  assoc_bss_beacon_int; int /*<<< orphan*/  assoc_bss_dtim_period; int /*<<< orphan*/  flags; TYPE_1__ target_stats; int /*<<< orphan*/  fw_vif_idx; int /*<<< orphan*/  bssid; } ;
struct ath6kl {int /*<<< orphan*/  sem; int /*<<< orphan*/  event_wq; int /*<<< orphan*/  wmi; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WLAN_CFG ; 
 int /*<<< orphan*/  ATH6KL_WAR_INVALID_RATE ; 
 int /*<<< orphan*/  BIT_ULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONNECTED ; 
 int /*<<< orphan*/  DTIM_PERIOD_AVAIL ; 
 int EBUSY ; 
 int EIO ; 
 int ENOENT ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int ETIMEDOUT ; 
 scalar_t__ INFRA_NETWORK ; 
 int /*<<< orphan*/  NL80211_STA_INFO_BSS_PARAM ; 
 int /*<<< orphan*/  NL80211_STA_INFO_RX_BYTES64 ; 
 int /*<<< orphan*/  NL80211_STA_INFO_RX_PACKETS ; 
 int /*<<< orphan*/  NL80211_STA_INFO_SIGNAL ; 
 int /*<<< orphan*/  NL80211_STA_INFO_TX_BITRATE ; 
 int /*<<< orphan*/  NL80211_STA_INFO_TX_BYTES64 ; 
 int /*<<< orphan*/  NL80211_STA_INFO_TX_PACKETS ; 
 int /*<<< orphan*/  RATE_INFO_BW_20 ; 
 int /*<<< orphan*/  RATE_INFO_BW_40 ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_MCS ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_SHORT_GI ; 
 int /*<<< orphan*/  STATS_UPDATE_PEND ; 
 int /*<<< orphan*/  WMI_TIMEOUT ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ath6kl_debug_war (struct ath6kl*,int /*<<< orphan*/ ) ; 
 struct ath6kl* ath6kl_priv (struct net_device*) ; 
 int ath6kl_wmi_get_stats_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 scalar_t__ is_rate_ht20 (int,void**,int*) ; 
 scalar_t__ is_rate_ht40 (int,void**,int*) ; 
 scalar_t__ is_rate_legacy (int) ; 
 scalar_t__ memcmp (void* const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath6kl_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_get_station(struct wiphy *wiphy, struct net_device *dev,
			      const u8 *mac, struct station_info *sinfo)
{
	struct ath6kl *ar = ath6kl_priv(dev);
	struct ath6kl_vif *vif = netdev_priv(dev);
	long left;
	bool sgi;
	s32 rate;
	int ret;
	u8 mcs;

	if (memcmp(mac, vif->bssid, ETH_ALEN) != 0)
		return -ENOENT;

	if (down_interruptible(&ar->sem))
		return -EBUSY;

	set_bit(STATS_UPDATE_PEND, &vif->flags);

	ret = ath6kl_wmi_get_stats_cmd(ar->wmi, vif->fw_vif_idx);

	if (ret != 0) {
		up(&ar->sem);
		return -EIO;
	}

	left = wait_event_interruptible_timeout(ar->event_wq,
						!test_bit(STATS_UPDATE_PEND,
							  &vif->flags),
						WMI_TIMEOUT);

	up(&ar->sem);

	if (left == 0)
		return -ETIMEDOUT;
	else if (left < 0)
		return left;

	if (vif->target_stats.rx_byte) {
		sinfo->rx_bytes = vif->target_stats.rx_byte;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_BYTES64);
		sinfo->rx_packets = vif->target_stats.rx_pkt;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_PACKETS);
	}

	if (vif->target_stats.tx_byte) {
		sinfo->tx_bytes = vif->target_stats.tx_byte;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BYTES64);
		sinfo->tx_packets = vif->target_stats.tx_pkt;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_PACKETS);
	}

	sinfo->signal = vif->target_stats.cs_rssi;
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL);

	rate = vif->target_stats.tx_ucast_rate;

	if (is_rate_legacy(rate)) {
		sinfo->txrate.legacy = rate / 100;
	} else if (is_rate_ht20(rate, &mcs, &sgi)) {
		if (sgi) {
			sinfo->txrate.flags |= RATE_INFO_FLAGS_SHORT_GI;
			sinfo->txrate.mcs = mcs - 1;
		} else {
			sinfo->txrate.mcs = mcs;
		}

		sinfo->txrate.flags |= RATE_INFO_FLAGS_MCS;
		sinfo->txrate.bw = RATE_INFO_BW_20;
	} else if (is_rate_ht40(rate, &mcs, &sgi)) {
		if (sgi) {
			sinfo->txrate.flags |= RATE_INFO_FLAGS_SHORT_GI;
			sinfo->txrate.mcs = mcs - 1;
		} else {
			sinfo->txrate.mcs = mcs;
		}

		sinfo->txrate.bw = RATE_INFO_BW_40;
		sinfo->txrate.flags |= RATE_INFO_FLAGS_MCS;
	} else {
		ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
			   "invalid rate from stats: %d\n", rate);
		ath6kl_debug_war(ar, ATH6KL_WAR_INVALID_RATE);
		return 0;
	}

	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BITRATE);

	if (test_bit(CONNECTED, &vif->flags) &&
	    test_bit(DTIM_PERIOD_AVAIL, &vif->flags) &&
	    vif->nw_type == INFRA_NETWORK) {
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_BSS_PARAM);
		sinfo->bss_param.flags = 0;
		sinfo->bss_param.dtim_period = vif->assoc_bss_dtim_period;
		sinfo->bss_param.beacon_interval = vif->assoc_bss_beacon_int;
	}

	return 0;
}