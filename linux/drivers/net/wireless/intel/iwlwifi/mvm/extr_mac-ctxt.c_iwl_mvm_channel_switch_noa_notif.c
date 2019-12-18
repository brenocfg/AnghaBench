#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_mvm_vif {int /*<<< orphan*/  csa_work; int /*<<< orphan*/  color; int /*<<< orphan*/  id; } ;
struct iwl_mvm {TYPE_2__* fw; int /*<<< orphan*/  csa_vif; int /*<<< orphan*/  cs_tx_unblock_dwork; int /*<<< orphan*/ * vif_id_to_mac; } ;
struct iwl_channel_switch_noa_notif {int /*<<< orphan*/  id_and_color; } ;
struct TYPE_3__ {int beacon_int; } ;
struct ieee80211_vif {int type; TYPE_1__ bss_conf; int /*<<< orphan*/  csa_active; } ;
struct TYPE_4__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 size_t FW_CMD_ID_AND_COLOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t FW_CTXT_ID_MSK ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_mvm*,char*) ; 
 int IWL_MVM_CS_UNBLOCK_TX_TIMEOUT ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_CHANNEL_SWITCH_CMD ; 
#define  NL80211_IFTYPE_AP 129 
#define  NL80211_IFTYPE_STATION 128 
 size_t NUM_MAC_INDEX_DRIVER ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (int,char*,size_t,size_t) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_chswitch_done (struct ieee80211_vif*,int) ; 
 int /*<<< orphan*/  ieee80211_csa_finish (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_csa_client_absent (struct iwl_mvm*,struct ieee80211_vif*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int iwl_rx_packet_payload_len (struct iwl_rx_packet*) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct ieee80211_vif* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void iwl_mvm_channel_switch_noa_notif(struct iwl_mvm *mvm,
				      struct iwl_rx_cmd_buffer *rxb)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_channel_switch_noa_notif *notif = (void *)pkt->data;
	struct ieee80211_vif *csa_vif, *vif;
	struct iwl_mvm_vif *mvmvif;
	int len = iwl_rx_packet_payload_len(pkt);
	u32 id_n_color, csa_id, mac_id;

	if (WARN_ON_ONCE(len < sizeof(*notif)))
		return;

	id_n_color = le32_to_cpu(notif->id_and_color);
	mac_id = id_n_color & FW_CTXT_ID_MSK;

	if (WARN_ON_ONCE(mac_id >= NUM_MAC_INDEX_DRIVER))
		return;

	rcu_read_lock();
	vif = rcu_dereference(mvm->vif_id_to_mac[mac_id]);
	mvmvif = iwl_mvm_vif_from_mac80211(vif);

	switch (vif->type) {
	case NL80211_IFTYPE_AP:
		csa_vif = rcu_dereference(mvm->csa_vif);
		if (WARN_ON(!csa_vif || !csa_vif->csa_active ||
			    csa_vif != vif))
			goto out_unlock;

		csa_id = FW_CMD_ID_AND_COLOR(mvmvif->id, mvmvif->color);
		if (WARN(csa_id != id_n_color,
			 "channel switch noa notification on unexpected vif (csa_vif=%d, notif=%d)",
			 csa_id, id_n_color))
			goto out_unlock;

		IWL_DEBUG_INFO(mvm, "Channel Switch Started Notification\n");

		schedule_delayed_work(&mvm->cs_tx_unblock_dwork,
				      msecs_to_jiffies(IWL_MVM_CS_UNBLOCK_TX_TIMEOUT *
						       csa_vif->bss_conf.beacon_int));

		ieee80211_csa_finish(csa_vif);

		rcu_read_unlock();

		RCU_INIT_POINTER(mvm->csa_vif, NULL);
		return;
	case NL80211_IFTYPE_STATION:
		if (!fw_has_capa(&mvm->fw->ucode_capa,
				 IWL_UCODE_TLV_CAPA_CHANNEL_SWITCH_CMD))
			iwl_mvm_csa_client_absent(mvm, vif);
		cancel_delayed_work(&mvmvif->csa_work);
		ieee80211_chswitch_done(vif, true);
		break;
	default:
		/* should never happen */
		WARN_ON_ONCE(1);
		break;
	}
out_unlock:
	rcu_read_unlock();
}