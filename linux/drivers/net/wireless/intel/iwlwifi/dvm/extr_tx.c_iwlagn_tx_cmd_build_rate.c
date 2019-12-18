#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct iwl_tx_cmd {int /*<<< orphan*/  rate_n_flags; int /*<<< orphan*/  tx_flags; scalar_t__ initial_rate_index; void* rts_retry_limit; void* data_retry_limit; } ;
struct iwl_priv {void* mgmt_tx_ant; TYPE_5__* nvm_data; scalar_t__ bt_full_concurrent; TYPE_4__* lib; scalar_t__ wowlan; } ;
struct TYPE_8__ {TYPE_1__* rates; } ;
struct ieee80211_tx_info {size_t band; TYPE_2__ control; } ;
struct ieee80211_sta {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_12__ {void* plcp; } ;
struct TYPE_11__ {int /*<<< orphan*/  valid_tx_ant; int /*<<< orphan*/ * bands; } ;
struct TYPE_10__ {TYPE_3__* bt_params; } ;
struct TYPE_9__ {scalar_t__ advanced_bt_coexist; } ;
struct TYPE_7__ {int idx; int flags; } ;

/* Variables and functions */
 int IEEE80211_TX_RC_MCS ; 
 void* IWLAGN_BAR_DFAULT_RETRY_LIMIT ; 
 void* IWLAGN_DEFAULT_TX_RETRY ; 
 void* IWLAGN_LOW_RETRY_LIMIT ; 
 void* IWLAGN_MGMT_DFAULT_RETRY_LIMIT ; 
 void* IWLAGN_RTS_DFAULT_RETRY_LIMIT ; 
 int IWL_FIRST_CCK_RATE ; 
 scalar_t__ IWL_FIRST_OFDM_RATE ; 
 int IWL_LAST_CCK_RATE ; 
 int IWL_RATE_COUNT_LEGACY ; 
 size_t NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  RATE_MCS_CCK_MSK ; 
 int /*<<< orphan*/  TX_CMD_FLG_STA_RATE_MSK ; 
 int /*<<< orphan*/  first_antenna (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_back_req (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_probe_resp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_ant_idx_to_flags (void*) ; 
 int /*<<< orphan*/  iwl_hw_set_rate_n_flags (void*,int /*<<< orphan*/ ) ; 
 TYPE_6__* iwl_rates ; 
 void* iwl_toggle_tx_ant (struct iwl_priv*,void*,int /*<<< orphan*/ ) ; 
 void* min (void*,void*) ; 
 int rate_lowest_index (int /*<<< orphan*/ *,struct ieee80211_sta*) ; 

__attribute__((used)) static void iwlagn_tx_cmd_build_rate(struct iwl_priv *priv,
				     struct iwl_tx_cmd *tx_cmd,
				     struct ieee80211_tx_info *info,
				     struct ieee80211_sta *sta,
				     __le16 fc)
{
	u32 rate_flags;
	int rate_idx;
	u8 rts_retry_limit;
	u8 data_retry_limit;
	u8 rate_plcp;

	if (priv->wowlan) {
		rts_retry_limit = IWLAGN_LOW_RETRY_LIMIT;
		data_retry_limit = IWLAGN_LOW_RETRY_LIMIT;
	} else {
		/* Set retry limit on RTS packets */
		rts_retry_limit = IWLAGN_RTS_DFAULT_RETRY_LIMIT;

		/* Set retry limit on DATA packets and Probe Responses*/
		if (ieee80211_is_probe_resp(fc)) {
			data_retry_limit = IWLAGN_MGMT_DFAULT_RETRY_LIMIT;
			rts_retry_limit =
				min(data_retry_limit, rts_retry_limit);
		} else if (ieee80211_is_back_req(fc))
			data_retry_limit = IWLAGN_BAR_DFAULT_RETRY_LIMIT;
		else
			data_retry_limit = IWLAGN_DEFAULT_TX_RETRY;
	}

	tx_cmd->data_retry_limit = data_retry_limit;
	tx_cmd->rts_retry_limit = rts_retry_limit;

	/* DATA packets will use the uCode station table for rate/antenna
	 * selection */
	if (ieee80211_is_data(fc)) {
		tx_cmd->initial_rate_index = 0;
		tx_cmd->tx_flags |= TX_CMD_FLG_STA_RATE_MSK;
		return;
	} else if (ieee80211_is_back_req(fc))
		tx_cmd->tx_flags |= TX_CMD_FLG_STA_RATE_MSK;

	/**
	 * If the current TX rate stored in mac80211 has the MCS bit set, it's
	 * not really a TX rate.  Thus, we use the lowest supported rate for
	 * this band.  Also use the lowest supported rate if the stored rate
	 * index is invalid.
	 */
	rate_idx = info->control.rates[0].idx;
	if (info->control.rates[0].flags & IEEE80211_TX_RC_MCS ||
			(rate_idx < 0) || (rate_idx > IWL_RATE_COUNT_LEGACY))
		rate_idx = rate_lowest_index(
				&priv->nvm_data->bands[info->band], sta);
	/* For 5 GHZ band, remap mac80211 rate indices into driver indices */
	if (info->band == NL80211_BAND_5GHZ)
		rate_idx += IWL_FIRST_OFDM_RATE;
	/* Get PLCP rate for tx_cmd->rate_n_flags */
	rate_plcp = iwl_rates[rate_idx].plcp;
	/* Zero out flags for this packet */
	rate_flags = 0;

	/* Set CCK flag as needed */
	if ((rate_idx >= IWL_FIRST_CCK_RATE) && (rate_idx <= IWL_LAST_CCK_RATE))
		rate_flags |= RATE_MCS_CCK_MSK;

	/* Set up antennas */
	if (priv->lib->bt_params &&
	    priv->lib->bt_params->advanced_bt_coexist &&
	    priv->bt_full_concurrent) {
		/* operated as 1x1 in full concurrency mode */
		priv->mgmt_tx_ant = iwl_toggle_tx_ant(priv, priv->mgmt_tx_ant,
				first_antenna(priv->nvm_data->valid_tx_ant));
	} else
		priv->mgmt_tx_ant = iwl_toggle_tx_ant(
					priv, priv->mgmt_tx_ant,
					priv->nvm_data->valid_tx_ant);
	rate_flags |= iwl_ant_idx_to_flags(priv->mgmt_tx_ant);

	/* Set the rate in the TX cmd */
	tx_cmd->rate_n_flags = iwl_hw_set_rate_n_flags(rate_plcp, rate_flags);
}