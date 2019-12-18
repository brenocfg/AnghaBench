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
struct iwl_tdls_config_res {int dummy; } ;
struct iwl_tdls_config_cmd {int tdls_peer_count; TYPE_1__* sta_info; void* tx_to_ap_ssn; void* tx_to_ap_tid; void* id_and_color; } ;
struct iwl_rx_packet {int dummy; } ;
struct iwl_mvm_vif {int /*<<< orphan*/  color; int /*<<< orphan*/  id; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * fw_id_to_mac_id; } ;
struct iwl_host_cmd {struct iwl_rx_packet* resp_pkt; int /*<<< orphan*/  len; int /*<<< orphan*/  data; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {scalar_t__ tdls_initiator; int /*<<< orphan*/  tdls; } ;
struct TYPE_2__ {int sta_id; void* is_initiator; void* tx_to_peer_ssn; void* tx_to_peer_tid; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMD_WANT_SKB ; 
 int FW_CMD_ID_AND_COLOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR_OR_NULL (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  IWL_DEBUG_TDLS (struct iwl_mvm*,char*,int) ; 
 void* IWL_MVM_TDLS_FW_TID ; 
 int /*<<< orphan*/  TDLS_CONFIG_CMD ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  iwl_free_resp (struct iwl_host_cmd*) ; 
 int iwl_mvm_send_cmd (struct iwl_mvm*,struct iwl_host_cmd*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int iwl_rx_packet_payload_len (struct iwl_rx_packet*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct ieee80211_sta* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_mvm_tdls_config(struct iwl_mvm *mvm, struct ieee80211_vif *vif)
{
	struct iwl_rx_packet *pkt;
	struct iwl_tdls_config_res *resp;
	struct iwl_tdls_config_cmd tdls_cfg_cmd = {};
	struct iwl_host_cmd cmd = {
		.id = TDLS_CONFIG_CMD,
		.flags = CMD_WANT_SKB,
		.data = { &tdls_cfg_cmd, },
		.len = { sizeof(struct iwl_tdls_config_cmd), },
	};
	struct ieee80211_sta *sta;
	int ret, i, cnt;
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);

	lockdep_assert_held(&mvm->mutex);

	tdls_cfg_cmd.id_and_color =
		cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvif->id, mvmvif->color));
	tdls_cfg_cmd.tx_to_ap_tid = IWL_MVM_TDLS_FW_TID;
	tdls_cfg_cmd.tx_to_ap_ssn = cpu_to_le16(0); /* not used for now */

	/* for now the Tx cmd is empty and unused */

	/* populate TDLS peer data */
	cnt = 0;
	for (i = 0; i < ARRAY_SIZE(mvm->fw_id_to_mac_id); i++) {
		sta = rcu_dereference_protected(mvm->fw_id_to_mac_id[i],
						lockdep_is_held(&mvm->mutex));
		if (IS_ERR_OR_NULL(sta) || !sta->tdls)
			continue;

		tdls_cfg_cmd.sta_info[cnt].sta_id = i;
		tdls_cfg_cmd.sta_info[cnt].tx_to_peer_tid =
							IWL_MVM_TDLS_FW_TID;
		tdls_cfg_cmd.sta_info[cnt].tx_to_peer_ssn = cpu_to_le16(0);
		tdls_cfg_cmd.sta_info[cnt].is_initiator =
				cpu_to_le32(sta->tdls_initiator ? 1 : 0);

		cnt++;
	}

	tdls_cfg_cmd.tdls_peer_count = cnt;
	IWL_DEBUG_TDLS(mvm, "send TDLS config to FW for %d peers\n", cnt);

	ret = iwl_mvm_send_cmd(mvm, &cmd);
	if (WARN_ON_ONCE(ret))
		return;

	pkt = cmd.resp_pkt;

	WARN_ON_ONCE(iwl_rx_packet_payload_len(pkt) != sizeof(*resp));

	/* we don't really care about the response at this point */

	iwl_free_resp(&cmd);
}