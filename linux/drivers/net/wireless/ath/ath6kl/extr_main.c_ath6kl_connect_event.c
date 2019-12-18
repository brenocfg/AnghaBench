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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ath6kl_vif {scalar_t__ nw_type; int /*<<< orphan*/  fw_vif_idx; int /*<<< orphan*/  flags; scalar_t__ reconnect_flag; TYPE_1__* aggr_cntxt; int /*<<< orphan*/  if_lock; int /*<<< orphan*/  ndev; int /*<<< orphan*/  listen_intvl_t; int /*<<< orphan*/  bss_ch; int /*<<< orphan*/  bssid; struct ath6kl* ar; } ;
struct ath6kl {int /*<<< orphan*/  wmi; int /*<<< orphan*/  usr_bss_filter; int /*<<< orphan*/  next_ep_id; scalar_t__ node_num; int /*<<< orphan*/  node_map; scalar_t__ ibss_ps_enable; } ;
typedef  enum network_type { ____Placeholder_network_type } network_type ;
struct TYPE_2__ {int /*<<< orphan*/  aggr_conn; } ;

/* Variables and functions */
 scalar_t__ ADHOC_NETWORK ; 
 int /*<<< orphan*/  CLEAR_BSSFILTER_ON_BEACON ; 
 int /*<<< orphan*/  CONNECTED ; 
 int /*<<< orphan*/  CONNECT_PEND ; 
 int /*<<< orphan*/  CURRENT_BSS_FILTER ; 
 int /*<<< orphan*/  ENDPOINT_2 ; 
 scalar_t__ INFRA_NETWORK ; 
 int /*<<< orphan*/  aggr_reset_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_cfg80211_connect_event (struct ath6kl_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath6kl_check_ch_switch (struct ath6kl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_wmi_bssfilter_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_wmi_listeninterval_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ath6kl_connect_event(struct ath6kl_vif *vif, u16 channel, u8 *bssid,
			  u16 listen_int, u16 beacon_int,
			  enum network_type net_type, u8 beacon_ie_len,
			  u8 assoc_req_len, u8 assoc_resp_len,
			  u8 *assoc_info)
{
	struct ath6kl *ar = vif->ar;

	ath6kl_cfg80211_connect_event(vif, channel, bssid,
				      listen_int, beacon_int,
				      net_type, beacon_ie_len,
				      assoc_req_len, assoc_resp_len,
				      assoc_info);

	memcpy(vif->bssid, bssid, sizeof(vif->bssid));
	vif->bss_ch = channel;

	if (vif->nw_type == INFRA_NETWORK) {
		ath6kl_wmi_listeninterval_cmd(ar->wmi, vif->fw_vif_idx,
					      vif->listen_intvl_t, 0);
		ath6kl_check_ch_switch(ar, channel);
	}

	netif_wake_queue(vif->ndev);

	/* Update connect & link status atomically */
	spin_lock_bh(&vif->if_lock);
	set_bit(CONNECTED, &vif->flags);
	clear_bit(CONNECT_PEND, &vif->flags);
	netif_carrier_on(vif->ndev);
	spin_unlock_bh(&vif->if_lock);

	aggr_reset_state(vif->aggr_cntxt->aggr_conn);
	vif->reconnect_flag = 0;

	if ((vif->nw_type == ADHOC_NETWORK) && ar->ibss_ps_enable) {
		memset(ar->node_map, 0, sizeof(ar->node_map));
		ar->node_num = 0;
		ar->next_ep_id = ENDPOINT_2;
	}

	if (!ar->usr_bss_filter) {
		set_bit(CLEAR_BSSFILTER_ON_BEACON, &vif->flags);
		ath6kl_wmi_bssfilter_cmd(ar->wmi, vif->fw_vif_idx,
					 CURRENT_BSS_FILTER, 0);
	}
}