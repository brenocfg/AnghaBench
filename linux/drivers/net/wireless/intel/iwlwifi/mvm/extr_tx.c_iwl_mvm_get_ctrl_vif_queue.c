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
struct iwl_mvm_vif {int cab_queue; } ;
struct iwl_mvm {int probe_queue; int p2p_dev_queue; } ;
struct TYPE_3__ {TYPE_2__* vif; } ;
struct ieee80211_tx_info {TYPE_1__ control; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {int type; } ;

/* Variables and functions */
#define  NL80211_IFTYPE_ADHOC 130 
#define  NL80211_IFTYPE_AP 129 
#define  NL80211_IFTYPE_P2P_DEVICE 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*,...) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ieee80211_has_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_bufferable_mmpdu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_deauth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_disassoc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_mgmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_probe_req (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (TYPE_2__*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_mvm_get_ctrl_vif_queue(struct iwl_mvm *mvm,
				      struct ieee80211_tx_info *info,
				      struct ieee80211_hdr *hdr)
{
	struct iwl_mvm_vif *mvmvif =
		iwl_mvm_vif_from_mac80211(info->control.vif);
	__le16 fc = hdr->frame_control;

	switch (info->control.vif->type) {
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_ADHOC:
		/*
		 * Non-bufferable frames use the broadcast station, thus they
		 * use the probe queue.
		 * Also take care of the case where we send a deauth to a
		 * station that we don't have, or similarly an association
		 * response (with non-success status) for a station we can't
		 * accept.
		 * Also, disassociate frames might happen, particular with
		 * reason 7 ("Class 3 frame received from nonassociated STA").
		 */
		if (ieee80211_is_mgmt(fc) &&
		    (!ieee80211_is_bufferable_mmpdu(fc) ||
		     ieee80211_is_deauth(fc) || ieee80211_is_disassoc(fc)))
			return mvm->probe_queue;

		if (!ieee80211_has_order(fc) && !ieee80211_is_probe_req(fc) &&
		    is_multicast_ether_addr(hdr->addr1))
			return mvmvif->cab_queue;

		WARN_ONCE(info->control.vif->type != NL80211_IFTYPE_ADHOC,
			  "fc=0x%02x", le16_to_cpu(fc));
		return mvm->probe_queue;
	case NL80211_IFTYPE_P2P_DEVICE:
		if (ieee80211_is_mgmt(fc))
			return mvm->p2p_dev_queue;

		WARN_ON_ONCE(1);
		return mvm->p2p_dev_queue;
	default:
		WARN_ONCE(1, "Not a ctrl vif, no available queue\n");
		return -1;
	}
}