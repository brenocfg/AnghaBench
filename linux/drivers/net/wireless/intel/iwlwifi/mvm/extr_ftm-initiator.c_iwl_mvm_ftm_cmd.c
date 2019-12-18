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
struct iwl_tof_range_req_cmd {int num_of_ap; void* tsf_mac_id; int /*<<< orphan*/  range_req_bssid; int /*<<< orphan*/ * macaddr_mask; int /*<<< orphan*/  macaddr_template; void* req_timeout_ms; int /*<<< orphan*/  request_id; void* initiator_flags; } ;
struct iwl_mvm_vif {int id; } ;
struct iwl_mvm {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bssid; scalar_t__ assoc; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;
struct cfg80211_pmsr_request {int n_peers; int timeout; TYPE_2__* peers; int /*<<< orphan*/ * mac_addr_mask; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  cookie; } ;
struct TYPE_4__ {scalar_t__ report_ap_tsf; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int IWL_TOF_INITIATOR_FLAGS_MACADDR_RANDOM ; 
 int IWL_TOF_INITIATOR_FLAGS_NON_ASAP_SUPPORT ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ ) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void iwl_mvm_ftm_cmd(struct iwl_mvm *mvm, struct ieee80211_vif *vif,
			    struct iwl_tof_range_req_cmd *cmd,
			    struct cfg80211_pmsr_request *req)
{
	int i;

	cmd->initiator_flags =
		cpu_to_le32(IWL_TOF_INITIATOR_FLAGS_MACADDR_RANDOM |
			    IWL_TOF_INITIATOR_FLAGS_NON_ASAP_SUPPORT);
	cmd->request_id = req->cookie;
	cmd->num_of_ap = req->n_peers;

	/*
	 * Use a large value for "no timeout". Don't use the maximum value
	 * because of fw limitations.
	 */
	if (req->timeout)
		cmd->req_timeout_ms = cpu_to_le32(req->timeout);
	else
		cmd->req_timeout_ms = cpu_to_le32(0xfffff);

	memcpy(cmd->macaddr_template, req->mac_addr, ETH_ALEN);
	for (i = 0; i < ETH_ALEN; i++)
		cmd->macaddr_mask[i] = ~req->mac_addr_mask[i];

	if (vif->bss_conf.assoc) {
		memcpy(cmd->range_req_bssid, vif->bss_conf.bssid, ETH_ALEN);

		/* AP's TSF is only relevant if associated */
		for (i = 0; i < req->n_peers; i++) {
			if (req->peers[i].report_ap_tsf) {
				struct iwl_mvm_vif *mvmvif =
					iwl_mvm_vif_from_mac80211(vif);

				cmd->tsf_mac_id = cpu_to_le32(mvmvif->id);
				return;
			}
		}
	} else {
		eth_broadcast_addr(cmd->range_req_bssid);
	}

	/* Don't report AP's TSF */
	cmd->tsf_mac_id = cpu_to_le32(0xff);
}