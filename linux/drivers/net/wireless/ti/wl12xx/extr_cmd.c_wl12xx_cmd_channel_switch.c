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
struct wl12xx_vif {int /*<<< orphan*/  role_id; } ;
struct wl12xx_cmd_channel_switch {scalar_t__ post_switch_tx_disable; int /*<<< orphan*/  stop_tx; int /*<<< orphan*/  switch_time; int /*<<< orphan*/  channel; int /*<<< orphan*/  role_id; } ;
struct wl1271 {int dummy; } ;
struct TYPE_4__ {TYPE_1__* chan; } ;
struct ieee80211_channel_switch {int /*<<< orphan*/  block_tx; int /*<<< orphan*/  count; TYPE_2__ chandef; } ;
struct TYPE_3__ {int /*<<< orphan*/  hw_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CHANNEL_SWITCH ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl12xx_cmd_channel_switch*) ; 
 struct wl12xx_cmd_channel_switch* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl12xx_cmd_channel_switch*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 

int wl12xx_cmd_channel_switch(struct wl1271 *wl,
			      struct wl12xx_vif *wlvif,
			      struct ieee80211_channel_switch *ch_switch)
{
	struct wl12xx_cmd_channel_switch *cmd;
	int ret;

	wl1271_debug(DEBUG_ACX, "cmd channel switch");

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		ret = -ENOMEM;
		goto out;
	}

	cmd->role_id = wlvif->role_id;
	cmd->channel = ch_switch->chandef.chan->hw_value;
	cmd->switch_time = ch_switch->count;
	cmd->stop_tx = ch_switch->block_tx;

	/* FIXME: control from mac80211 in the future */
	/* Enable TX on the target channel */
	cmd->post_switch_tx_disable = 0;

	ret = wl1271_cmd_send(wl, CMD_CHANNEL_SWITCH, cmd, sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("failed to send channel switch command");
		goto out_free;
	}

out_free:
	kfree(cmd);

out:
	return ret;
}