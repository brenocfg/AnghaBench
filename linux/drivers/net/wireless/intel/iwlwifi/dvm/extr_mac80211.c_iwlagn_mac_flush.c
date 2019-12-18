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
typedef  int u32 ;
struct iwl_priv {int /*<<< orphan*/  mutex; TYPE_3__* trans; int /*<<< orphan*/  status; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_6__ {TYPE_2__* trans_cfg; } ;
struct TYPE_5__ {TYPE_1__* base_params; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_of_queues; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  IWL_DEBUG_TX (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_priv*,char*,...) ; 
 int /*<<< orphan*/  IWL_DEFAULT_CMD_QUEUE_NUM ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  IWL_IPAN_CMD_QUEUE_NUM ; 
 struct iwl_priv* IWL_MAC80211_GET_DVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  STATUS_EXIT_PENDING ; 
 scalar_t__ iwl_is_rfkill (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwl_trans_wait_tx_queues_empty (TYPE_3__*,int) ; 
 scalar_t__ iwlagn_txfifo_flush (struct iwl_priv*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwlagn_mac_flush(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
			     u32 queues, bool drop)
{
	struct iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	u32 scd_queues;

	mutex_lock(&priv->mutex);
	IWL_DEBUG_MAC80211(priv, "enter\n");

	if (test_bit(STATUS_EXIT_PENDING, &priv->status)) {
		IWL_DEBUG_TX(priv, "Aborting flush due to device shutdown\n");
		goto done;
	}
	if (iwl_is_rfkill(priv)) {
		IWL_DEBUG_TX(priv, "Aborting flush due to RF Kill\n");
		goto done;
	}

	scd_queues = BIT(priv->trans->trans_cfg->base_params->num_of_queues) - 1;
	scd_queues &= ~(BIT(IWL_IPAN_CMD_QUEUE_NUM) |
			BIT(IWL_DEFAULT_CMD_QUEUE_NUM));

	if (drop) {
		IWL_DEBUG_TX_QUEUES(priv, "Flushing SCD queues: 0x%x\n",
				    scd_queues);
		if (iwlagn_txfifo_flush(priv, scd_queues)) {
			IWL_ERR(priv, "flush request fail\n");
			goto done;
		}
	}

	IWL_DEBUG_TX_QUEUES(priv, "wait transmit/flush all frames\n");
	iwl_trans_wait_tx_queues_empty(priv->trans, scd_queues);
done:
	mutex_unlock(&priv->mutex);
	IWL_DEBUG_MAC80211(priv, "leave\n");
}