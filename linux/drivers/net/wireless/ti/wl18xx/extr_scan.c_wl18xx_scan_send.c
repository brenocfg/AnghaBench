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
typedef  int /*<<< orphan*/  u8 ;
struct wlcore_scan_channels {scalar_t__ role_id; int rssi_threshold; int total_cycles; scalar_t__ dfs; scalar_t__* active; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  tag; int /*<<< orphan*/  rate; scalar_t__ terminate_after; int /*<<< orphan*/  n_probe_reqs; scalar_t__ protect; scalar_t__ urgency; scalar_t__ add_broadcast; scalar_t__ filter; scalar_t__ ssid_from_list; int /*<<< orphan*/  bss_type; scalar_t__ snr_threshold; int /*<<< orphan*/  scan_type; } ;
struct wl18xx_cmd_scan_params {scalar_t__ role_id; int rssi_threshold; int total_cycles; scalar_t__ dfs; scalar_t__* active; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  tag; int /*<<< orphan*/  rate; scalar_t__ terminate_after; int /*<<< orphan*/  n_probe_reqs; scalar_t__ protect; scalar_t__ urgency; scalar_t__ add_broadcast; scalar_t__ filter; scalar_t__ ssid_from_list; int /*<<< orphan*/  bss_type; scalar_t__ snr_threshold; int /*<<< orphan*/  scan_type; } ;
struct wl12xx_vif {scalar_t__ dev_role_id; scalar_t__ role_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_probe_reqs; } ;
struct TYPE_5__ {TYPE_1__ scan; } ;
struct wl1271 {TYPE_2__ conf; } ;
struct cfg80211_scan_request {int n_ssids; int /*<<< orphan*/  ie_len; int /*<<< orphan*/  ie; TYPE_3__* ssids; scalar_t__ no_cck; int /*<<< orphan*/  n_channels; int /*<<< orphan*/  channels; } ;
struct TYPE_6__ {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/ * ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SCAN ; 
 int /*<<< orphan*/  DEBUG_SCAN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  SCAN_BSS_TYPE_ANY ; 
 int /*<<< orphan*/  SCAN_TYPE_SEARCH ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WL1271_SCAN_DEFAULT_TAG ; 
 scalar_t__ WL12XX_INVALID_ROLE_ID ; 
 int /*<<< orphan*/  WL18XX_SCAN_RATE_6 ; 
 int /*<<< orphan*/  kfree (struct wlcore_scan_channels*) ; 
 struct wlcore_scan_channels* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wlcore_scan_channels*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_dump (int /*<<< orphan*/ ,char*,struct wlcore_scan_channels*,int) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 
 int wl12xx_cmd_build_probe_req (struct wl1271*,struct wl12xx_vif*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wl18xx_adjust_channels (struct wlcore_scan_channels*,struct wlcore_scan_channels*) ; 
 scalar_t__ wlcore_is_p2p_mgmt (struct wl12xx_vif*) ; 
 int /*<<< orphan*/  wlcore_set_scan_chan_params (struct wl1271*,struct wlcore_scan_channels*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wl18xx_scan_send(struct wl1271 *wl, struct wl12xx_vif *wlvif,
			    struct cfg80211_scan_request *req)
{
	struct wl18xx_cmd_scan_params *cmd;
	struct wlcore_scan_channels *cmd_channels = NULL;
	int ret;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		ret = -ENOMEM;
		goto out;
	}

	/* scan on the dev role if the regular one is not started */
	if (wlcore_is_p2p_mgmt(wlvif))
		cmd->role_id = wlvif->dev_role_id;
	else
		cmd->role_id = wlvif->role_id;

	if (WARN_ON(cmd->role_id == WL12XX_INVALID_ROLE_ID)) {
		ret = -EINVAL;
		goto out;
	}

	cmd->scan_type = SCAN_TYPE_SEARCH;
	cmd->rssi_threshold = -127;
	cmd->snr_threshold = 0;

	cmd->bss_type = SCAN_BSS_TYPE_ANY;

	cmd->ssid_from_list = 0;
	cmd->filter = 0;
	cmd->add_broadcast = 0;

	cmd->urgency = 0;
	cmd->protect = 0;

	cmd->n_probe_reqs = wl->conf.scan.num_probe_reqs;
	cmd->terminate_after = 0;

	/* configure channels */
	WARN_ON(req->n_ssids > 1);

	cmd_channels = kzalloc(sizeof(*cmd_channels), GFP_KERNEL);
	if (!cmd_channels) {
		ret = -ENOMEM;
		goto out;
	}

	wlcore_set_scan_chan_params(wl, cmd_channels, req->channels,
				    req->n_channels, req->n_ssids,
				    SCAN_TYPE_SEARCH);
	wl18xx_adjust_channels(cmd, cmd_channels);

	/*
	 * all the cycles params (except total cycles) should
	 * remain 0 for normal scan
	 */
	cmd->total_cycles = 1;

	if (req->no_cck)
		cmd->rate = WL18XX_SCAN_RATE_6;

	cmd->tag = WL1271_SCAN_DEFAULT_TAG;

	if (req->n_ssids) {
		cmd->ssid_len = req->ssids[0].ssid_len;
		memcpy(cmd->ssid, req->ssids[0].ssid, cmd->ssid_len);
	}

	/* TODO: per-band ies? */
	if (cmd->active[0]) {
		u8 band = NL80211_BAND_2GHZ;
		ret = wl12xx_cmd_build_probe_req(wl, wlvif,
				 cmd->role_id, band,
				 req->ssids ? req->ssids[0].ssid : NULL,
				 req->ssids ? req->ssids[0].ssid_len : 0,
				 req->ie,
				 req->ie_len,
				 NULL,
				 0,
				 false);
		if (ret < 0) {
			wl1271_error("2.4GHz PROBE request template failed");
			goto out;
		}
	}

	if (cmd->active[1] || cmd->dfs) {
		u8 band = NL80211_BAND_5GHZ;
		ret = wl12xx_cmd_build_probe_req(wl, wlvif,
				 cmd->role_id, band,
				 req->ssids ? req->ssids[0].ssid : NULL,
				 req->ssids ? req->ssids[0].ssid_len : 0,
				 req->ie,
				 req->ie_len,
				 NULL,
				 0,
				 false);
		if (ret < 0) {
			wl1271_error("5GHz PROBE request template failed");
			goto out;
		}
	}

	wl1271_dump(DEBUG_SCAN, "SCAN: ", cmd, sizeof(*cmd));

	ret = wl1271_cmd_send(wl, CMD_SCAN, cmd, sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("SCAN failed");
		goto out;
	}

out:
	kfree(cmd_channels);
	kfree(cmd);
	return ret;
}