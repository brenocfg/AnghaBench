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
typedef  size_t u16 ;
struct wcn36xx_sta {size_t tid; int /*<<< orphan*/  ampdu_lock; int /*<<< orphan*/ * ampdu_state; } ;
struct wcn36xx {int /*<<< orphan*/  conf_mutex; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {struct wcn36xx* priv; } ;
struct ieee80211_ampdu_params {int action; size_t tid; size_t ssn; struct ieee80211_sta* sta; } ;
typedef  enum ieee80211_ampdu_mlme_action { ____Placeholder_ieee80211_ampdu_mlme_action } ieee80211_ampdu_mlme_action ;

/* Variables and functions */
#define  IEEE80211_AMPDU_RX_START 134 
#define  IEEE80211_AMPDU_RX_STOP 133 
#define  IEEE80211_AMPDU_TX_OPERATIONAL 132 
#define  IEEE80211_AMPDU_TX_START 131 
#define  IEEE80211_AMPDU_TX_STOP_CONT 130 
#define  IEEE80211_AMPDU_TX_STOP_FLUSH 129 
#define  IEEE80211_AMPDU_TX_STOP_FLUSH_CONT 128 
 int /*<<< orphan*/  WCN36XX_AMPDU_NONE ; 
 int /*<<< orphan*/  WCN36XX_AMPDU_OPERATIONAL ; 
 int /*<<< orphan*/  WCN36XX_AMPDU_START ; 
 int /*<<< orphan*/  WCN36XX_DBG_MAC ; 
 int /*<<< orphan*/  get_sta_index (struct ieee80211_vif*,struct wcn36xx_sta*) ; 
 int /*<<< orphan*/  ieee80211_start_tx_ba_cb_irqsafe (struct ieee80211_vif*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ieee80211_stop_tx_ba_cb_irqsafe (struct ieee80211_vif*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,int,size_t) ; 
 int /*<<< orphan*/  wcn36xx_err (char*) ; 
 int /*<<< orphan*/  wcn36xx_smd_add_ba (struct wcn36xx*) ; 
 int /*<<< orphan*/  wcn36xx_smd_add_ba_session (struct wcn36xx*,struct ieee80211_sta*,size_t,size_t*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_smd_del_ba (struct wcn36xx*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_smd_trigger_ba (struct wcn36xx*,int /*<<< orphan*/ ) ; 
 struct wcn36xx_sta* wcn36xx_sta_to_priv (struct ieee80211_sta*) ; 

__attribute__((used)) static int wcn36xx_ampdu_action(struct ieee80211_hw *hw,
		    struct ieee80211_vif *vif,
		    struct ieee80211_ampdu_params *params)
{
	struct wcn36xx *wcn = hw->priv;
	struct wcn36xx_sta *sta_priv = wcn36xx_sta_to_priv(params->sta);
	struct ieee80211_sta *sta = params->sta;
	enum ieee80211_ampdu_mlme_action action = params->action;
	u16 tid = params->tid;
	u16 *ssn = &params->ssn;

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac ampdu action action %d tid %d\n",
		    action, tid);

	mutex_lock(&wcn->conf_mutex);

	switch (action) {
	case IEEE80211_AMPDU_RX_START:
		sta_priv->tid = tid;
		wcn36xx_smd_add_ba_session(wcn, sta, tid, ssn, 0,
			get_sta_index(vif, sta_priv));
		wcn36xx_smd_add_ba(wcn);
		wcn36xx_smd_trigger_ba(wcn, get_sta_index(vif, sta_priv));
		break;
	case IEEE80211_AMPDU_RX_STOP:
		wcn36xx_smd_del_ba(wcn, tid, get_sta_index(vif, sta_priv));
		break;
	case IEEE80211_AMPDU_TX_START:
		spin_lock_bh(&sta_priv->ampdu_lock);
		sta_priv->ampdu_state[tid] = WCN36XX_AMPDU_START;
		spin_unlock_bh(&sta_priv->ampdu_lock);

		ieee80211_start_tx_ba_cb_irqsafe(vif, sta->addr, tid);
		break;
	case IEEE80211_AMPDU_TX_OPERATIONAL:
		spin_lock_bh(&sta_priv->ampdu_lock);
		sta_priv->ampdu_state[tid] = WCN36XX_AMPDU_OPERATIONAL;
		spin_unlock_bh(&sta_priv->ampdu_lock);

		wcn36xx_smd_add_ba_session(wcn, sta, tid, ssn, 1,
			get_sta_index(vif, sta_priv));
		break;
	case IEEE80211_AMPDU_TX_STOP_FLUSH:
	case IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
	case IEEE80211_AMPDU_TX_STOP_CONT:
		spin_lock_bh(&sta_priv->ampdu_lock);
		sta_priv->ampdu_state[tid] = WCN36XX_AMPDU_NONE;
		spin_unlock_bh(&sta_priv->ampdu_lock);

		ieee80211_stop_tx_ba_cb_irqsafe(vif, sta->addr, tid);
		break;
	default:
		wcn36xx_err("Unknown AMPDU action\n");
	}

	mutex_unlock(&wcn->conf_mutex);

	return 0;
}