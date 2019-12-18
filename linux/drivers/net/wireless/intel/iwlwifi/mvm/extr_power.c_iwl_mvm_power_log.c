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
struct iwl_mvm {int dummy; } ;
struct iwl_mac_power_cmd {int flags; int keep_alive_seconds; int /*<<< orphan*/  uapsd_max_sp; int /*<<< orphan*/  uapsd_ac_flags; int /*<<< orphan*/  qndp_tid; int /*<<< orphan*/  tx_data_timeout_uapsd; int /*<<< orphan*/  rx_data_timeout_uapsd; int /*<<< orphan*/  lprx_rssi_threshold; int /*<<< orphan*/  skip_dtim_periods; int /*<<< orphan*/  tx_data_timeout; int /*<<< orphan*/  rx_data_timeout; int /*<<< orphan*/  id_and_color; } ;
struct TYPE_2__ {int /*<<< orphan*/  power_scheme; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_POWER (struct iwl_mvm*,char*,...) ; 
 int /*<<< orphan*/  POWER_FLAGS_ADVANCE_PM_ENA_MSK ; 
 int /*<<< orphan*/  POWER_FLAGS_LPRX_ENA_MSK ; 
 int /*<<< orphan*/  POWER_FLAGS_POWER_MANAGEMENT_ENA_MSK ; 
 int /*<<< orphan*/  POWER_FLAGS_SKIP_OVER_DTIM_MSK ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 TYPE_1__ iwlmvm_mod_params ; 
 int /*<<< orphan*/  le16_to_cpu (int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_mvm_power_log(struct iwl_mvm *mvm,
			      struct iwl_mac_power_cmd *cmd)
{
	IWL_DEBUG_POWER(mvm,
			"Sending power table command on mac id 0x%X for power level %d, flags = 0x%X\n",
			cmd->id_and_color, iwlmvm_mod_params.power_scheme,
			le16_to_cpu(cmd->flags));
	IWL_DEBUG_POWER(mvm, "Keep alive = %u sec\n",
			le16_to_cpu(cmd->keep_alive_seconds));

	if (!(cmd->flags & cpu_to_le16(POWER_FLAGS_POWER_MANAGEMENT_ENA_MSK))) {
		IWL_DEBUG_POWER(mvm, "Disable power management\n");
		return;
	}

	IWL_DEBUG_POWER(mvm, "Rx timeout = %u usec\n",
			le32_to_cpu(cmd->rx_data_timeout));
	IWL_DEBUG_POWER(mvm, "Tx timeout = %u usec\n",
			le32_to_cpu(cmd->tx_data_timeout));
	if (cmd->flags & cpu_to_le16(POWER_FLAGS_SKIP_OVER_DTIM_MSK))
		IWL_DEBUG_POWER(mvm, "DTIM periods to skip = %u\n",
				cmd->skip_dtim_periods);
	if (cmd->flags & cpu_to_le16(POWER_FLAGS_LPRX_ENA_MSK))
		IWL_DEBUG_POWER(mvm, "LP RX RSSI threshold = %u\n",
				cmd->lprx_rssi_threshold);
	if (cmd->flags & cpu_to_le16(POWER_FLAGS_ADVANCE_PM_ENA_MSK)) {
		IWL_DEBUG_POWER(mvm, "uAPSD enabled\n");
		IWL_DEBUG_POWER(mvm, "Rx timeout (uAPSD) = %u usec\n",
				le32_to_cpu(cmd->rx_data_timeout_uapsd));
		IWL_DEBUG_POWER(mvm, "Tx timeout (uAPSD) = %u usec\n",
				le32_to_cpu(cmd->tx_data_timeout_uapsd));
		IWL_DEBUG_POWER(mvm, "QNDP TID = %d\n", cmd->qndp_tid);
		IWL_DEBUG_POWER(mvm, "ACs flags = 0x%x\n", cmd->uapsd_ac_flags);
		IWL_DEBUG_POWER(mvm, "Max SP = %d\n", cmd->uapsd_max_sp);
	}
}