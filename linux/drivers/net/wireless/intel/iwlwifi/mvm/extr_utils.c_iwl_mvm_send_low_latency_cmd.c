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
typedef  int /*<<< orphan*/  u16 ;
struct iwl_mvm {TYPE_1__* fw; } ;
struct iwl_mac_low_latency_cmd {int low_latency_rx; int low_latency_tx; int /*<<< orphan*/  mac_id; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_DYNAMIC_QUOTA ; 
 int /*<<< orphan*/  LOW_LATENCY_CMD ; 
 int /*<<< orphan*/  MAC_CONF_GROUP ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_cmd_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_mac_low_latency_cmd*) ; 

void iwl_mvm_send_low_latency_cmd(struct iwl_mvm *mvm,
				  bool low_latency, u16 mac_id)
{
	struct iwl_mac_low_latency_cmd cmd = {
		.mac_id = cpu_to_le32(mac_id)
	};

	if (!fw_has_capa(&mvm->fw->ucode_capa,
			 IWL_UCODE_TLV_CAPA_DYNAMIC_QUOTA))
		return;

	if (low_latency) {
		/* currently we don't care about the direction */
		cmd.low_latency_rx = 1;
		cmd.low_latency_tx = 1;
	}

	if (iwl_mvm_send_cmd_pdu(mvm, iwl_cmd_id(LOW_LATENCY_CMD,
						 MAC_CONF_GROUP, 0),
				 0, sizeof(cmd), &cmd))
		IWL_ERR(mvm, "Failed to send low latency command\n");
}