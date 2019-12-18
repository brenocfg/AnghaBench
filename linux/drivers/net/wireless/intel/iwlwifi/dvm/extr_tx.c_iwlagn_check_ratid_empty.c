#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_10__ {int state; int /*<<< orphan*/  ssn; int /*<<< orphan*/  txq_id; } ;
struct iwl_tid_data {TYPE_5__ agg; int /*<<< orphan*/  next_reclaimed; } ;
struct iwl_priv {int /*<<< orphan*/  trans; struct iwl_tid_data** tid_data; TYPE_4__* contexts; TYPE_3__* stations; int /*<<< orphan*/  sta_lock; } ;
struct ieee80211_vif {int dummy; } ;
typedef  enum iwl_rxon_context_id { ____Placeholder_iwl_rxon_context_id } iwl_rxon_context_id ;
struct TYPE_9__ {struct ieee80211_vif* vif; } ;
struct TYPE_6__ {size_t* addr; } ;
struct TYPE_7__ {TYPE_1__ sta; } ;
struct TYPE_8__ {int ctxid; TYPE_2__ sta; } ;

/* Variables and functions */
 int IWL_AGG_OFF ; 
 int IWL_AGG_STARTING ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_priv*,char*,int /*<<< orphan*/ ) ; 
#define  IWL_EMPTYING_HW_QUEUE_ADDBA 129 
#define  IWL_EMPTYING_HW_QUEUE_DELBA 128 
 int /*<<< orphan*/  ieee80211_start_tx_ba_cb_irqsafe (struct ieee80211_vif*,size_t*,size_t) ; 
 int /*<<< orphan*/  ieee80211_stop_tx_ba_cb_irqsafe (struct ieee80211_vif*,size_t*,size_t) ; 
 int /*<<< orphan*/  iwl_trans_txq_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwlagn_dealloc_agg_txq (struct iwl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwlagn_check_ratid_empty(struct iwl_priv *priv, int sta_id, u8 tid)
{
	struct iwl_tid_data *tid_data = &priv->tid_data[sta_id][tid];
	enum iwl_rxon_context_id ctx;
	struct ieee80211_vif *vif;
	u8 *addr;

	lockdep_assert_held(&priv->sta_lock);

	addr = priv->stations[sta_id].sta.sta.addr;
	ctx = priv->stations[sta_id].ctxid;
	vif = priv->contexts[ctx].vif;

	switch (priv->tid_data[sta_id][tid].agg.state) {
	case IWL_EMPTYING_HW_QUEUE_DELBA:
		/* There are no packets for this RA / TID in the HW any more */
		if (tid_data->agg.ssn == tid_data->next_reclaimed) {
			IWL_DEBUG_TX_QUEUES(priv,
				"Can continue DELBA flow ssn = next_recl = %d\n",
				tid_data->next_reclaimed);
			iwl_trans_txq_disable(priv->trans,
					      tid_data->agg.txq_id, true);
			iwlagn_dealloc_agg_txq(priv, tid_data->agg.txq_id);
			tid_data->agg.state = IWL_AGG_OFF;
			ieee80211_stop_tx_ba_cb_irqsafe(vif, addr, tid);
		}
		break;
	case IWL_EMPTYING_HW_QUEUE_ADDBA:
		/* There are no packets for this RA / TID in the HW any more */
		if (tid_data->agg.ssn == tid_data->next_reclaimed) {
			IWL_DEBUG_TX_QUEUES(priv,
				"Can continue ADDBA flow ssn = next_recl = %d\n",
				tid_data->next_reclaimed);
			tid_data->agg.state = IWL_AGG_STARTING;
			ieee80211_start_tx_ba_cb_irqsafe(vif, addr, tid);
		}
		break;
	default:
		break;
	}
}