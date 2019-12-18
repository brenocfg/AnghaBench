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
struct iwl_tof_range_req_cmd_v5 {int req_timeout; int macaddr_random; int /*<<< orphan*/  range_req_bssid; int /*<<< orphan*/ * macaddr_mask; int /*<<< orphan*/  macaddr_template; int /*<<< orphan*/  num_of_ap; int /*<<< orphan*/  request_id; } ;
struct iwl_mvm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bssid; scalar_t__ assoc; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;
struct cfg80211_pmsr_request {int timeout; int /*<<< orphan*/ * mac_addr_mask; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  n_peers; int /*<<< orphan*/  cookie; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void iwl_mvm_ftm_cmd_v5(struct iwl_mvm *mvm, struct ieee80211_vif *vif,
			       struct iwl_tof_range_req_cmd_v5 *cmd,
			       struct cfg80211_pmsr_request *req)
{
	int i;

	cmd->request_id = req->cookie;
	cmd->num_of_ap = req->n_peers;

	/* use maximum for "no timeout" or bigger than what we can do */
	if (!req->timeout || req->timeout > 255 * 100)
		cmd->req_timeout = 255;
	else
		cmd->req_timeout = DIV_ROUND_UP(req->timeout, 100);

	/*
	 * We treat it always as random, since if not we'll
	 * have filled our local address there instead.
	 */
	cmd->macaddr_random = 1;
	memcpy(cmd->macaddr_template, req->mac_addr, ETH_ALEN);
	for (i = 0; i < ETH_ALEN; i++)
		cmd->macaddr_mask[i] = ~req->mac_addr_mask[i];

	if (vif->bss_conf.assoc)
		memcpy(cmd->range_req_bssid, vif->bss_conf.bssid, ETH_ALEN);
	else
		eth_broadcast_addr(cmd->range_req_bssid);
}