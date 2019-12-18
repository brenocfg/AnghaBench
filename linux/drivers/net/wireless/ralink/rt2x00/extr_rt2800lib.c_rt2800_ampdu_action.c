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
typedef  int /*<<< orphan*/  u16 ;
struct rt2x00_sta {scalar_t__ wcid; } ;
struct rt2x00_dev {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct ieee80211_hw {scalar_t__ priv; } ;
struct ieee80211_ampdu_params {int action; int /*<<< orphan*/  tid; struct ieee80211_sta* sta; } ;
typedef  enum ieee80211_ampdu_mlme_action { ____Placeholder_ieee80211_ampdu_mlme_action } ieee80211_ampdu_mlme_action ;

/* Variables and functions */
#define  IEEE80211_AMPDU_RX_START 134 
#define  IEEE80211_AMPDU_RX_STOP 133 
#define  IEEE80211_AMPDU_TX_OPERATIONAL 132 
#define  IEEE80211_AMPDU_TX_START 131 
#define  IEEE80211_AMPDU_TX_STOP_CONT 130 
#define  IEEE80211_AMPDU_TX_STOP_FLUSH 129 
#define  IEEE80211_AMPDU_TX_STOP_FLUSH_CONT 128 
 scalar_t__ WCID_END ; 
 int /*<<< orphan*/  ieee80211_start_tx_ba_cb_irqsafe (struct ieee80211_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_stop_tx_ba_cb_irqsafe (struct ieee80211_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_warn (struct rt2x00_dev*,char*) ; 

int rt2800_ampdu_action(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
			struct ieee80211_ampdu_params *params)
{
	struct ieee80211_sta *sta = params->sta;
	enum ieee80211_ampdu_mlme_action action = params->action;
	u16 tid = params->tid;
	struct rt2x00_sta *sta_priv = (struct rt2x00_sta *)sta->drv_priv;
	int ret = 0;

	/*
	 * Don't allow aggregation for stations the hardware isn't aware
	 * of because tx status reports for frames to an unknown station
	 * always contain wcid=WCID_END+1 and thus we can't distinguish
	 * between multiple stations which leads to unwanted situations
	 * when the hw reorders frames due to aggregation.
	 */
	if (sta_priv->wcid > WCID_END)
		return 1;

	switch (action) {
	case IEEE80211_AMPDU_RX_START:
	case IEEE80211_AMPDU_RX_STOP:
		/*
		 * The hw itself takes care of setting up BlockAck mechanisms.
		 * So, we only have to allow mac80211 to nagotiate a BlockAck
		 * agreement. Once that is done, the hw will BlockAck incoming
		 * AMPDUs without further setup.
		 */
		break;
	case IEEE80211_AMPDU_TX_START:
		ieee80211_start_tx_ba_cb_irqsafe(vif, sta->addr, tid);
		break;
	case IEEE80211_AMPDU_TX_STOP_CONT:
	case IEEE80211_AMPDU_TX_STOP_FLUSH:
	case IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		ieee80211_stop_tx_ba_cb_irqsafe(vif, sta->addr, tid);
		break;
	case IEEE80211_AMPDU_TX_OPERATIONAL:
		break;
	default:
		rt2x00_warn((struct rt2x00_dev *)hw->priv,
			    "Unknown AMPDU action\n");
	}

	return ret;
}