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
typedef  int u16 ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct ath_common {int dummy; } ;
struct ath9k_htc_target_aggr {int tidno; int aggr_enable; int /*<<< orphan*/  sta_index; } ;
struct ath9k_htc_sta {int /*<<< orphan*/ * tid_state; int /*<<< orphan*/  index; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_lock; } ;
struct ath9k_htc_priv {TYPE_1__ tx; int /*<<< orphan*/  ah; } ;
typedef  enum ieee80211_ampdu_mlme_action { ____Placeholder_ieee80211_ampdu_mlme_action } ieee80211_ampdu_mlme_action ;

/* Variables and functions */
 int /*<<< orphan*/  AGGR_START ; 
 int /*<<< orphan*/  AGGR_STOP ; 
 int ATH9K_HTC_MAX_TID ; 
 int /*<<< orphan*/  CONFIG ; 
 int EINVAL ; 
 int IEEE80211_AMPDU_TX_START ; 
 int /*<<< orphan*/  WMI_CMD_BUF (int /*<<< orphan*/ ,struct ath9k_htc_target_aggr*) ; 
 int /*<<< orphan*/  WMI_TX_AGGR_ENABLE_CMDID ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ath9k_htc_target_aggr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath9k_htc_tx_aggr_oper(struct ath9k_htc_priv *priv,
				  struct ieee80211_vif *vif,
				  struct ieee80211_sta *sta,
				  enum ieee80211_ampdu_mlme_action action,
				  u16 tid)
{
	struct ath_common *common = ath9k_hw_common(priv->ah);
	struct ath9k_htc_target_aggr aggr;
	struct ath9k_htc_sta *ista;
	int ret = 0;
	u8 cmd_rsp;

	if (tid >= ATH9K_HTC_MAX_TID)
		return -EINVAL;

	memset(&aggr, 0, sizeof(struct ath9k_htc_target_aggr));
	ista = (struct ath9k_htc_sta *) sta->drv_priv;

	aggr.sta_index = ista->index;
	aggr.tidno = tid & 0xf;
	aggr.aggr_enable = (action == IEEE80211_AMPDU_TX_START) ? true : false;

	WMI_CMD_BUF(WMI_TX_AGGR_ENABLE_CMDID, &aggr);
	if (ret)
		ath_dbg(common, CONFIG,
			"Unable to %s TX aggregation for (%pM, %d)\n",
			(aggr.aggr_enable) ? "start" : "stop", sta->addr, tid);
	else
		ath_dbg(common, CONFIG,
			"%s TX aggregation for (%pM, %d)\n",
			(aggr.aggr_enable) ? "Starting" : "Stopping",
			sta->addr, tid);

	spin_lock_bh(&priv->tx.tx_lock);
	ista->tid_state[tid] = (aggr.aggr_enable && !ret) ? AGGR_START : AGGR_STOP;
	spin_unlock_bh(&priv->tx.tx_lock);

	return ret;
}