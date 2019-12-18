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
struct net_device {int dummy; } ;
struct cfg80211_connect_resp_params {int /*<<< orphan*/  resp_ie_len; int /*<<< orphan*/  resp_ie; int /*<<< orphan*/  req_ie_len; int /*<<< orphan*/  req_ie; int /*<<< orphan*/  bssid; int /*<<< orphan*/  status; } ;
struct brcmf_if {TYPE_1__* vif; } ;
struct brcmf_event_msg {int dummy; } ;
struct brcmf_cfg80211_profile {int /*<<< orphan*/  bssid; } ;
struct brcmf_cfg80211_info {int dummy; } ;
struct brcmf_cfg80211_connect_info {int /*<<< orphan*/  resp_ie_len; int /*<<< orphan*/  resp_ie; int /*<<< orphan*/  req_ie_len; int /*<<< orphan*/  req_ie; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  conn_params ;
struct TYPE_2__ {int /*<<< orphan*/  sme_state; struct brcmf_cfg80211_profile profile; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_VIF_STATUS_CONNECTED ; 
 int /*<<< orphan*/  BRCMF_VIF_STATUS_CONNECTING ; 
 int /*<<< orphan*/  CONN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  WLAN_STATUS_AUTH_TIMEOUT ; 
 int /*<<< orphan*/  WLAN_STATUS_SUCCESS ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  brcmf_get_assoc_ies (struct brcmf_cfg80211_info*,struct brcmf_if*) ; 
 int /*<<< orphan*/  brcmf_update_bss_info (struct brcmf_cfg80211_info*,struct brcmf_if*) ; 
 int /*<<< orphan*/  cfg80211_connect_done (struct net_device*,struct cfg80211_connect_resp_params*,int /*<<< orphan*/ ) ; 
 struct brcmf_cfg80211_connect_info* cfg_to_conn (struct brcmf_cfg80211_info*) ; 
 int /*<<< orphan*/  memset (struct cfg80211_connect_resp_params*,int /*<<< orphan*/ ,int) ; 
 struct brcmf_if* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32
brcmf_bss_connect_done(struct brcmf_cfg80211_info *cfg,
		       struct net_device *ndev, const struct brcmf_event_msg *e,
		       bool completed)
{
	struct brcmf_if *ifp = netdev_priv(ndev);
	struct brcmf_cfg80211_profile *profile = &ifp->vif->profile;
	struct brcmf_cfg80211_connect_info *conn_info = cfg_to_conn(cfg);
	struct cfg80211_connect_resp_params conn_params;

	brcmf_dbg(TRACE, "Enter\n");

	if (test_and_clear_bit(BRCMF_VIF_STATUS_CONNECTING,
			       &ifp->vif->sme_state)) {
		memset(&conn_params, 0, sizeof(conn_params));
		if (completed) {
			brcmf_get_assoc_ies(cfg, ifp);
			brcmf_update_bss_info(cfg, ifp);
			set_bit(BRCMF_VIF_STATUS_CONNECTED,
				&ifp->vif->sme_state);
			conn_params.status = WLAN_STATUS_SUCCESS;
		} else {
			conn_params.status = WLAN_STATUS_AUTH_TIMEOUT;
		}
		conn_params.bssid = profile->bssid;
		conn_params.req_ie = conn_info->req_ie;
		conn_params.req_ie_len = conn_info->req_ie_len;
		conn_params.resp_ie = conn_info->resp_ie;
		conn_params.resp_ie_len = conn_info->resp_ie_len;
		cfg80211_connect_done(ndev, &conn_params, GFP_KERNEL);
		brcmf_dbg(CONN, "Report connect result - connection %s\n",
			  completed ? "succeeded" : "failed");
	}
	brcmf_dbg(TRACE, "Exit\n");
	return 0;
}