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
struct TYPE_5__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  bw; scalar_t__ nss; int /*<<< orphan*/  mcs; scalar_t__ legacy; } ;
struct station_info {int /*<<< orphan*/  filled; TYPE_2__ txrate; int /*<<< orphan*/  rx_duration; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  bw; scalar_t__ nss; int /*<<< orphan*/  mcs; scalar_t__ legacy; } ;
struct ath10k_sta {TYPE_3__ txrate; int /*<<< orphan*/  rx_duration; TYPE_1__* arvif; } ;
struct ath10k {int dummy; } ;
struct TYPE_4__ {struct ath10k* ar; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL80211_STA_INFO_RX_DURATION ; 
 int /*<<< orphan*/  NL80211_STA_INFO_TX_BITRATE ; 
 int /*<<< orphan*/  ath10k_peer_stats_enabled (struct ath10k*) ; 

__attribute__((used)) static void ath10k_sta_statistics(struct ieee80211_hw *hw,
				  struct ieee80211_vif *vif,
				  struct ieee80211_sta *sta,
				  struct station_info *sinfo)
{
	struct ath10k_sta *arsta = (struct ath10k_sta *)sta->drv_priv;
	struct ath10k *ar = arsta->arvif->ar;

	if (!ath10k_peer_stats_enabled(ar))
		return;

	sinfo->rx_duration = arsta->rx_duration;
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_DURATION);

	if (!arsta->txrate.legacy && !arsta->txrate.nss)
		return;

	if (arsta->txrate.legacy) {
		sinfo->txrate.legacy = arsta->txrate.legacy;
	} else {
		sinfo->txrate.mcs = arsta->txrate.mcs;
		sinfo->txrate.nss = arsta->txrate.nss;
		sinfo->txrate.bw = arsta->txrate.bw;
	}
	sinfo->txrate.flags = arsta->txrate.flags;
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BITRATE);
}