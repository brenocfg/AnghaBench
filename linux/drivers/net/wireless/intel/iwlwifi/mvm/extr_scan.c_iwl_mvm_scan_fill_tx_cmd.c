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
struct iwl_scan_req_tx_cmd {int /*<<< orphan*/  sta_id; void* rate_n_flags; void* tx_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  sta_id; } ;
struct iwl_mvm {TYPE_1__ aux_sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  NL80211_BAND_5GHZ ; 
 int TX_CMD_FLG_BT_DIS ; 
 int TX_CMD_FLG_SEQ_CTL ; 
 void* cpu_to_le32 (int) ; 
 void* iwl_mvm_scan_rate_n_flags (struct iwl_mvm*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void iwl_mvm_scan_fill_tx_cmd(struct iwl_mvm *mvm,
				     struct iwl_scan_req_tx_cmd *tx_cmd,
				     bool no_cck)
{
	tx_cmd[0].tx_flags = cpu_to_le32(TX_CMD_FLG_SEQ_CTL |
					 TX_CMD_FLG_BT_DIS);
	tx_cmd[0].rate_n_flags = iwl_mvm_scan_rate_n_flags(mvm,
							   NL80211_BAND_2GHZ,
							   no_cck);
	tx_cmd[0].sta_id = mvm->aux_sta.sta_id;

	tx_cmd[1].tx_flags = cpu_to_le32(TX_CMD_FLG_SEQ_CTL |
					 TX_CMD_FLG_BT_DIS);
	tx_cmd[1].rate_n_flags = iwl_mvm_scan_rate_n_flags(mvm,
							   NL80211_BAND_5GHZ,
							   no_cck);
	tx_cmd[1].sta_id = mvm->aux_sta.sta_id;
}