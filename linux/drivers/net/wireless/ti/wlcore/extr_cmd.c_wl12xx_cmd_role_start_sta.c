#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {size_t hlid; int /*<<< orphan*/  role_chan_type; } ;
struct wl12xx_vif {scalar_t__ band; int basic_rate_set; TYPE_3__ sta; int /*<<< orphan*/  channel_type; int /*<<< orphan*/  rate_set; int /*<<< orphan*/  role_id; scalar_t__ p2p; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  beacon_int; int /*<<< orphan*/  channel; } ;
struct TYPE_5__ {size_t hlid; int /*<<< orphan*/  session; void* remote_rates; void* local_rates; int /*<<< orphan*/  bssid; int /*<<< orphan*/  ssid; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid_type; int /*<<< orphan*/  beacon_interval; void* basic_rate_set; } ;
struct wl12xx_cmd_role_start {TYPE_2__ sta; int /*<<< orphan*/  channel_type; int /*<<< orphan*/  channel; int /*<<< orphan*/  band; int /*<<< orphan*/  role_id; } ;
struct wl1271 {int /*<<< orphan*/ * session_ids; } ;
struct TYPE_4__ {int /*<<< orphan*/  bssid; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ROLE_START ; 
 int CONF_TX_CCK_RATES ; 
 int CONF_TX_ENABLED_RATES ; 
 int CONF_TX_MCS_RATES ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 size_t WL12XX_INVALID_LINK_ID ; 
 int /*<<< orphan*/  WL12XX_SSID_TYPE_ANY ; 
 int /*<<< orphan*/  WLCORE_BAND_5GHZ ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  kfree (struct wl12xx_cmd_role_start*) ; 
 struct wl12xx_cmd_role_start* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl12xx_cmd_role_start*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 
 int wl12xx_allocate_link (struct wl1271*,struct wl12xx_vif*,size_t*) ; 
 int /*<<< orphan*/  wl12xx_free_link (struct wl1271*,struct wl12xx_vif*,size_t*) ; 
 struct ieee80211_vif* wl12xx_wlvif_to_vif (struct wl12xx_vif*) ; 
 int /*<<< orphan*/  wlcore_get_native_channel_type (int /*<<< orphan*/ ) ; 
 int wlcore_hw_sta_get_ap_rate_mask (struct wl1271*,struct wl12xx_vif*) ; 

int wl12xx_cmd_role_start_sta(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	struct ieee80211_vif *vif = wl12xx_wlvif_to_vif(wlvif);
	struct wl12xx_cmd_role_start *cmd;
	u32 supported_rates;
	int ret;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		ret = -ENOMEM;
		goto out;
	}

	wl1271_debug(DEBUG_CMD, "cmd role start sta %d", wlvif->role_id);

	cmd->role_id = wlvif->role_id;
	if (wlvif->band == NL80211_BAND_5GHZ)
		cmd->band = WLCORE_BAND_5GHZ;
	cmd->channel = wlvif->channel;
	cmd->sta.basic_rate_set = cpu_to_le32(wlvif->basic_rate_set);
	cmd->sta.beacon_interval = cpu_to_le16(wlvif->beacon_int);
	cmd->sta.ssid_type = WL12XX_SSID_TYPE_ANY;
	cmd->sta.ssid_len = wlvif->ssid_len;
	memcpy(cmd->sta.ssid, wlvif->ssid, wlvif->ssid_len);
	memcpy(cmd->sta.bssid, vif->bss_conf.bssid, ETH_ALEN);

	supported_rates = CONF_TX_ENABLED_RATES | CONF_TX_MCS_RATES |
			  wlcore_hw_sta_get_ap_rate_mask(wl, wlvif);
	if (wlvif->p2p)
		supported_rates &= ~CONF_TX_CCK_RATES;

	cmd->sta.local_rates = cpu_to_le32(supported_rates);

	cmd->channel_type = wlcore_get_native_channel_type(wlvif->channel_type);

	if (wlvif->sta.hlid == WL12XX_INVALID_LINK_ID) {
		ret = wl12xx_allocate_link(wl, wlvif, &wlvif->sta.hlid);
		if (ret)
			goto out_free;
	}
	cmd->sta.hlid = wlvif->sta.hlid;
	cmd->sta.session = wl->session_ids[wlvif->sta.hlid];
	/*
	 * We don't have the correct remote rates in this stage.  The
	 * rates will be reconfigured later, after association, if the
	 * firmware supports ACX_PEER_CAP.  Otherwise, there's nothing
	 * we can do, so use all supported_rates here.
	 */
	cmd->sta.remote_rates = cpu_to_le32(supported_rates);

	wl1271_debug(DEBUG_CMD, "role start: roleid=%d, hlid=%d, session=%d "
		     "basic_rate_set: 0x%x, remote_rates: 0x%x",
		     wlvif->role_id, cmd->sta.hlid, cmd->sta.session,
		     wlvif->basic_rate_set, wlvif->rate_set);

	ret = wl1271_cmd_send(wl, CMD_ROLE_START, cmd, sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("failed to initiate cmd role start sta");
		goto err_hlid;
	}

	wlvif->sta.role_chan_type = wlvif->channel_type;
	goto out_free;

err_hlid:
	/* clear links on error. */
	wl12xx_free_link(wl, wlvif, &wlvif->sta.hlid);

out_free:
	kfree(cmd);

out:
	return ret;
}