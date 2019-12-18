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
struct iwl_tx_cmd {int /*<<< orphan*/  rate_n_flags; int /*<<< orphan*/  tx_flags; scalar_t__ initial_rate_index; int /*<<< orphan*/  data_retry_limit; int /*<<< orphan*/  rts_retry_limit; } ;
struct iwl_mvm_sta {scalar_t__ sta_state; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_tx_info {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ IEEE80211_STA_AUTHORIZED ; 
 int /*<<< orphan*/  IWL_BAR_DFAULT_RETRY_LIMIT ; 
 int /*<<< orphan*/  IWL_DEFAULT_TX_RETRY ; 
 int /*<<< orphan*/  IWL_MGMT_DFAULT_RETRY_LIMIT ; 
 int /*<<< orphan*/  IWL_RTS_DFAULT_RETRY_LIMIT ; 
 int TX_CMD_FLG_ACK ; 
 int TX_CMD_FLG_BAR ; 
 int TX_CMD_FLG_STA_RATE ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 scalar_t__ ieee80211_is_back_req (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_probe_resp (int /*<<< orphan*/ ) ; 
 int iwl_mvm_get_tx_rate_n_flags (struct iwl_mvm*,struct ieee80211_tx_info*,struct ieee80211_sta*,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void iwl_mvm_set_tx_cmd_rate(struct iwl_mvm *mvm, struct iwl_tx_cmd *tx_cmd,
			    struct ieee80211_tx_info *info,
			    struct ieee80211_sta *sta, __le16 fc)
{
	/* Set retry limit on RTS packets */
	tx_cmd->rts_retry_limit = IWL_RTS_DFAULT_RETRY_LIMIT;

	/* Set retry limit on DATA packets and Probe Responses*/
	if (ieee80211_is_probe_resp(fc)) {
		tx_cmd->data_retry_limit = IWL_MGMT_DFAULT_RETRY_LIMIT;
		tx_cmd->rts_retry_limit =
			min(tx_cmd->data_retry_limit, tx_cmd->rts_retry_limit);
	} else if (ieee80211_is_back_req(fc)) {
		tx_cmd->data_retry_limit = IWL_BAR_DFAULT_RETRY_LIMIT;
	} else {
		tx_cmd->data_retry_limit = IWL_DEFAULT_TX_RETRY;
	}

	/*
	 * for data packets, rate info comes from the table inside the fw. This
	 * table is controlled by LINK_QUALITY commands
	 */

	if (ieee80211_is_data(fc) && sta) {
		struct iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);

		if (mvmsta->sta_state >= IEEE80211_STA_AUTHORIZED) {
			tx_cmd->initial_rate_index = 0;
			tx_cmd->tx_flags |= cpu_to_le32(TX_CMD_FLG_STA_RATE);
			return;
		}
	} else if (ieee80211_is_back_req(fc)) {
		tx_cmd->tx_flags |=
			cpu_to_le32(TX_CMD_FLG_ACK | TX_CMD_FLG_BAR);
	}

	/* Set the rate in the TX cmd */
	tx_cmd->rate_n_flags =
		cpu_to_le32(iwl_mvm_get_tx_rate_n_flags(mvm, info, sta, fc));
}