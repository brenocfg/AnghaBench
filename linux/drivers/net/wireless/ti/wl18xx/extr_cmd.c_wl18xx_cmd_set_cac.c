#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wlcore_cmd_cac_start {int /*<<< orphan*/  bandwidth; int /*<<< orphan*/  band; int /*<<< orphan*/  channel; int /*<<< orphan*/  role_id; } ;
struct wl12xx_vif {scalar_t__ band; int /*<<< orphan*/  channel_type; int /*<<< orphan*/  channel; int /*<<< orphan*/  role_id; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CAC_START ; 
 int /*<<< orphan*/  CMD_CAC_STOP ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  WLCORE_BAND_5GHZ ; 
 int /*<<< orphan*/  kfree (struct wlcore_cmd_cac_start*) ; 
 struct wlcore_cmd_cac_start* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wlcore_cmd_cac_start*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 
 int /*<<< orphan*/  wlcore_get_native_channel_type (int /*<<< orphan*/ ) ; 

int wl18xx_cmd_set_cac(struct wl1271 *wl, struct wl12xx_vif *wlvif, bool start)
{
	struct wlcore_cmd_cac_start *cmd;
	int ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd cac (channel %d) %s",
		     wlvif->channel, start ? "start" : "stop");

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	cmd->role_id = wlvif->role_id;
	cmd->channel = wlvif->channel;
	if (wlvif->band == NL80211_BAND_5GHZ)
		cmd->band = WLCORE_BAND_5GHZ;
	cmd->bandwidth = wlcore_get_native_channel_type(wlvif->channel_type);

	ret = wl1271_cmd_send(wl,
			      start ? CMD_CAC_START : CMD_CAC_STOP,
			      cmd, sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("failed to send cac command");
		goto out_free;
	}

out_free:
	kfree(cmd);
	return ret;
}