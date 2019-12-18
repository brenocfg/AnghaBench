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
typedef  int u16 ;
struct mwl8k_priv {int /*<<< orphan*/  wmm_enabled; int /*<<< orphan*/ * wmm_params; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_tx_queue_params {int /*<<< orphan*/  txop; int /*<<< orphan*/  aifs; int /*<<< orphan*/  cw_max; int /*<<< orphan*/  cw_min; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MWL8K_TX_WMM_QUEUES ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ieee80211_tx_queue_params const*,int) ; 
 int mwl8k_cmd_set_edca_params (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mwl8k_cmd_set_wmm_mode (struct ieee80211_hw*,int) ; 
 int mwl8k_fw_lock (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mwl8k_fw_unlock (struct ieee80211_hw*) ; 

__attribute__((used)) static int mwl8k_conf_tx(struct ieee80211_hw *hw,
			 struct ieee80211_vif *vif, u16 queue,
			 const struct ieee80211_tx_queue_params *params)
{
	struct mwl8k_priv *priv = hw->priv;
	int rc;

	rc = mwl8k_fw_lock(hw);
	if (!rc) {
		BUG_ON(queue > MWL8K_TX_WMM_QUEUES - 1);
		memcpy(&priv->wmm_params[queue], params, sizeof(*params));

		if (!priv->wmm_enabled)
			rc = mwl8k_cmd_set_wmm_mode(hw, 1);

		if (!rc) {
			int q = MWL8K_TX_WMM_QUEUES - 1 - queue;
			rc = mwl8k_cmd_set_edca_params(hw, q,
						       params->cw_min,
						       params->cw_max,
						       params->aifs,
						       params->txop);
		}

		mwl8k_fw_unlock(hw);
	}

	return rc;
}