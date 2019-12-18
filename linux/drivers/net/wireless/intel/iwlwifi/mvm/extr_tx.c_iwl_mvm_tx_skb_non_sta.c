#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  cb; scalar_t__ data; } ;
struct TYPE_9__ {int /*<<< orphan*/  sta_id; } ;
struct TYPE_8__ {int /*<<< orphan*/  sta_id; } ;
struct iwl_mvm_vif {TYPE_2__ mcast_sta; TYPE_1__ bcast_sta; } ;
struct TYPE_12__ {int /*<<< orphan*/  sta_id; } ;
struct TYPE_10__ {int /*<<< orphan*/  sta_id; } ;
struct iwl_mvm {int snif_queue; int aux_queue; int /*<<< orphan*/  trans; TYPE_5__ aux_sta; TYPE_3__ snif_sta; } ;
struct iwl_device_cmd {int dummy; } ;
struct TYPE_11__ {TYPE_6__* vif; } ;
struct ieee80211_tx_info {int flags; TYPE_4__ control; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_14__ {int flags; } ;
struct TYPE_13__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_MAX_DATA_LEN ; 
 TYPE_7__* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int IEEE80211_TX_CTL_TX_OFFCHAN ; 
 int /*<<< orphan*/  IWL_DEBUG_TX (struct iwl_mvm*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 scalar_t__ IWL_MVM_NON_TRANSMITTING_AP ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
 scalar_t__ NL80211_IFTYPE_P2P_DEVICE ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_data (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_probe_resp (int /*<<< orphan*/ ) ; 
 int iwl_mvm_get_ctrl_vif_queue (struct iwl_mvm*,struct ieee80211_tx_info*,struct ieee80211_hdr*) ; 
 int /*<<< orphan*/  iwl_mvm_probe_resp_set_noa (struct iwl_mvm*,struct sk_buff*) ; 
 struct iwl_device_cmd* iwl_mvm_set_tx_params (struct iwl_mvm*,struct sk_buff*,struct ieee80211_tx_info*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_skb_prepare_status (struct sk_buff*,struct iwl_device_cmd*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (TYPE_6__*) ; 
 int /*<<< orphan*/  iwl_trans_free_tx_cmd (int /*<<< orphan*/ ,struct iwl_device_cmd*) ; 
 scalar_t__ iwl_trans_tx (int /*<<< orphan*/ ,struct sk_buff*,struct iwl_device_cmd*,int) ; 
 int /*<<< orphan*/  memcpy (struct ieee80211_tx_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (scalar_t__) ; 

int iwl_mvm_tx_skb_non_sta(struct iwl_mvm *mvm, struct sk_buff *skb)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	struct ieee80211_tx_info info;
	struct iwl_device_cmd *dev_cmd;
	u8 sta_id;
	int hdrlen = ieee80211_hdrlen(hdr->frame_control);
	__le16 fc = hdr->frame_control;
	bool offchannel = IEEE80211_SKB_CB(skb)->flags &
		IEEE80211_TX_CTL_TX_OFFCHAN;
	int queue = -1;

	if (IWL_MVM_NON_TRANSMITTING_AP && ieee80211_is_probe_resp(fc))
		return -1;

	memcpy(&info, skb->cb, sizeof(info));

	if (WARN_ON_ONCE(skb->len > IEEE80211_MAX_DATA_LEN + hdrlen))
		return -1;

	if (WARN_ON_ONCE(info.flags & IEEE80211_TX_CTL_AMPDU))
		return -1;

	if (info.control.vif) {
		struct iwl_mvm_vif *mvmvif =
			iwl_mvm_vif_from_mac80211(info.control.vif);

		if (info.control.vif->type == NL80211_IFTYPE_P2P_DEVICE ||
		    info.control.vif->type == NL80211_IFTYPE_AP ||
		    info.control.vif->type == NL80211_IFTYPE_ADHOC) {
			if (!ieee80211_is_data(hdr->frame_control))
				sta_id = mvmvif->bcast_sta.sta_id;
			else
				sta_id = mvmvif->mcast_sta.sta_id;

			queue = iwl_mvm_get_ctrl_vif_queue(mvm, &info, hdr);
		} else if (info.control.vif->type == NL80211_IFTYPE_MONITOR) {
			queue = mvm->snif_queue;
			sta_id = mvm->snif_sta.sta_id;
		} else if (info.control.vif->type == NL80211_IFTYPE_STATION &&
			   offchannel) {
			/*
			 * IWL_MVM_OFFCHANNEL_QUEUE is used for ROC packets
			 * that can be used in 2 different types of vifs, P2P &
			 * STATION.
			 * P2P uses the offchannel queue.
			 * STATION (HS2.0) uses the auxiliary context of the FW,
			 * and hence needs to be sent on the aux queue.
			 */
			sta_id = mvm->aux_sta.sta_id;
			queue = mvm->aux_queue;
		}
	}

	if (queue < 0) {
		IWL_ERR(mvm, "No queue was found. Dropping TX\n");
		return -1;
	}

	if (unlikely(ieee80211_is_probe_resp(fc)))
		iwl_mvm_probe_resp_set_noa(mvm, skb);

	IWL_DEBUG_TX(mvm, "station Id %d, queue=%d\n", sta_id, queue);

	dev_cmd = iwl_mvm_set_tx_params(mvm, skb, &info, hdrlen, NULL, sta_id);
	if (!dev_cmd)
		return -1;

	/* From now on, we cannot access info->control */
	iwl_mvm_skb_prepare_status(skb, dev_cmd);

	if (iwl_trans_tx(mvm->trans, skb, dev_cmd, queue)) {
		iwl_trans_free_tx_cmd(mvm->trans, dev_cmd);
		return -1;
	}

	return 0;
}