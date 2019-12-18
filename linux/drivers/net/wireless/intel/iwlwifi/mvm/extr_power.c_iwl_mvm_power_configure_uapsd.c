#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ use_ps_poll; } ;
struct iwl_mvm_vif {TYPE_2__* queue_params; TYPE_1__ dbgfs_pm; } ;
struct TYPE_8__ {scalar_t__ cur_fw_img; } ;
struct iwl_mvm {TYPE_4__ fwrt; TYPE_3__* hw; } ;
struct iwl_mac_power_cmd {int flags; int uapsd_ac_flags; int qndp_tid; int snooze_interval; int snooze_window; int /*<<< orphan*/  heavy_rx_thld_percentage; int /*<<< orphan*/  heavy_tx_thld_percentage; int /*<<< orphan*/  heavy_rx_thld_packets; int /*<<< orphan*/  heavy_tx_thld_packets; void* tx_data_timeout_uapsd; void* rx_data_timeout_uapsd; int /*<<< orphan*/  uapsd_max_sp; } ;
struct ieee80211_vif {int dummy; } ;
typedef  enum ieee80211_ac_numbers { ____Placeholder_ieee80211_ac_numbers } ieee80211_ac_numbers ;
struct TYPE_7__ {int /*<<< orphan*/  uapsd_max_sp_len; } ;
struct TYPE_6__ {int /*<<< orphan*/  acm; int /*<<< orphan*/  uapsd; } ;

/* Variables and functions */
 int BIT (int const) ; 
#define  IEEE80211_AC_BE 131 
#define  IEEE80211_AC_BK 130 
#define  IEEE80211_AC_VI 129 
#define  IEEE80211_AC_VO 128 
 int /*<<< orphan*/  IWL_MVM_PS_HEAVY_RX_THLD_PACKETS ; 
 int /*<<< orphan*/  IWL_MVM_PS_HEAVY_RX_THLD_PERCENT ; 
 int /*<<< orphan*/  IWL_MVM_PS_HEAVY_TX_THLD_PACKETS ; 
 int /*<<< orphan*/  IWL_MVM_PS_HEAVY_TX_THLD_PERCENT ; 
 int /*<<< orphan*/  IWL_MVM_PS_SNOOZE_HEAVY_RX_THLD_PACKETS ; 
 int /*<<< orphan*/  IWL_MVM_PS_SNOOZE_HEAVY_TX_THLD_PACKETS ; 
 int /*<<< orphan*/  IWL_MVM_PS_SNOOZE_INTERVAL ; 
 int /*<<< orphan*/  IWL_MVM_PS_SNOOZE_WINDOW ; 
 int /*<<< orphan*/  IWL_MVM_UAPSD_RX_DATA_TIMEOUT ; 
 int /*<<< orphan*/  IWL_MVM_UAPSD_TX_DATA_TIMEOUT ; 
 int /*<<< orphan*/  IWL_MVM_WOWLAN_PS_RX_DATA_TIMEOUT ; 
 int /*<<< orphan*/  IWL_MVM_WOWLAN_PS_SNOOZE_WINDOW ; 
 int /*<<< orphan*/  IWL_MVM_WOWLAN_PS_TX_DATA_TIMEOUT ; 
 scalar_t__ IWL_UCODE_WOWLAN ; 
 int /*<<< orphan*/  POWER_FLAGS_ADVANCE_PM_ENA_MSK ; 
 int /*<<< orphan*/  POWER_FLAGS_SNOOZE_ENA_MSK ; 
 int /*<<< orphan*/  POWER_FLAGS_UAPSD_MISBEHAVING_ENA_MSK ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

__attribute__((used)) static void iwl_mvm_power_configure_uapsd(struct iwl_mvm *mvm,
					  struct ieee80211_vif *vif,
					  struct iwl_mac_power_cmd *cmd)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	enum ieee80211_ac_numbers ac;
	bool tid_found = false;

#ifdef CONFIG_IWLWIFI_DEBUGFS
	/* set advanced pm flag with no uapsd ACs to enable ps-poll */
	if (mvmvif->dbgfs_pm.use_ps_poll) {
		cmd->flags |= cpu_to_le16(POWER_FLAGS_ADVANCE_PM_ENA_MSK);
		return;
	}
#endif

	for (ac = IEEE80211_AC_VO; ac <= IEEE80211_AC_BK; ac++) {
		if (!mvmvif->queue_params[ac].uapsd)
			continue;

		if (mvm->fwrt.cur_fw_img != IWL_UCODE_WOWLAN)
			cmd->flags |=
				cpu_to_le16(POWER_FLAGS_ADVANCE_PM_ENA_MSK);

		cmd->uapsd_ac_flags |= BIT(ac);

		/* QNDP TID - the highest TID with no admission control */
		if (!tid_found && !mvmvif->queue_params[ac].acm) {
			tid_found = true;
			switch (ac) {
			case IEEE80211_AC_VO:
				cmd->qndp_tid = 6;
				break;
			case IEEE80211_AC_VI:
				cmd->qndp_tid = 5;
				break;
			case IEEE80211_AC_BE:
				cmd->qndp_tid = 0;
				break;
			case IEEE80211_AC_BK:
				cmd->qndp_tid = 1;
				break;
			}
		}
	}

	cmd->flags |= cpu_to_le16(POWER_FLAGS_UAPSD_MISBEHAVING_ENA_MSK);

	if (cmd->uapsd_ac_flags == (BIT(IEEE80211_AC_VO) |
				    BIT(IEEE80211_AC_VI) |
				    BIT(IEEE80211_AC_BE) |
				    BIT(IEEE80211_AC_BK))) {
		cmd->flags |= cpu_to_le16(POWER_FLAGS_SNOOZE_ENA_MSK);
		cmd->snooze_interval = cpu_to_le16(IWL_MVM_PS_SNOOZE_INTERVAL);
		cmd->snooze_window =
			(mvm->fwrt.cur_fw_img == IWL_UCODE_WOWLAN) ?
				cpu_to_le16(IWL_MVM_WOWLAN_PS_SNOOZE_WINDOW) :
				cpu_to_le16(IWL_MVM_PS_SNOOZE_WINDOW);
	}

	cmd->uapsd_max_sp = mvm->hw->uapsd_max_sp_len;

	if (mvm->fwrt.cur_fw_img == IWL_UCODE_WOWLAN || cmd->flags &
	    cpu_to_le16(POWER_FLAGS_SNOOZE_ENA_MSK)) {
		cmd->rx_data_timeout_uapsd =
			cpu_to_le32(IWL_MVM_WOWLAN_PS_RX_DATA_TIMEOUT);
		cmd->tx_data_timeout_uapsd =
			cpu_to_le32(IWL_MVM_WOWLAN_PS_TX_DATA_TIMEOUT);
	} else {
		cmd->rx_data_timeout_uapsd =
			cpu_to_le32(IWL_MVM_UAPSD_RX_DATA_TIMEOUT);
		cmd->tx_data_timeout_uapsd =
			cpu_to_le32(IWL_MVM_UAPSD_TX_DATA_TIMEOUT);
	}

	if (cmd->flags & cpu_to_le16(POWER_FLAGS_SNOOZE_ENA_MSK)) {
		cmd->heavy_tx_thld_packets =
			IWL_MVM_PS_SNOOZE_HEAVY_TX_THLD_PACKETS;
		cmd->heavy_rx_thld_packets =
			IWL_MVM_PS_SNOOZE_HEAVY_RX_THLD_PACKETS;
	} else {
		cmd->heavy_tx_thld_packets =
			IWL_MVM_PS_HEAVY_TX_THLD_PACKETS;
		cmd->heavy_rx_thld_packets =
			IWL_MVM_PS_HEAVY_RX_THLD_PACKETS;
	}
	cmd->heavy_tx_thld_percentage =
		IWL_MVM_PS_HEAVY_TX_THLD_PERCENT;
	cmd->heavy_rx_thld_percentage =
		IWL_MVM_PS_HEAVY_RX_THLD_PERCENT;
}