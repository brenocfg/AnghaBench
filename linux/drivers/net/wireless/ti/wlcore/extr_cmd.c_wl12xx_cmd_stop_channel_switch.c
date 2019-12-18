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
struct wl12xx_vif {int /*<<< orphan*/  role_id; } ;
struct wl12xx_cmd_stop_channel_switch {int /*<<< orphan*/  role_id; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_STOP_CHANNEL_SWICTH ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl12xx_cmd_stop_channel_switch*) ; 
 struct wl12xx_cmd_stop_channel_switch* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl12xx_cmd_stop_channel_switch*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 

int wl12xx_cmd_stop_channel_switch(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	struct wl12xx_cmd_stop_channel_switch *cmd;
	int ret;

	wl1271_debug(DEBUG_ACX, "cmd stop channel switch");

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		ret = -ENOMEM;
		goto out;
	}

	cmd->role_id = wlvif->role_id;

	ret = wl1271_cmd_send(wl, CMD_STOP_CHANNEL_SWICTH, cmd, sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("failed to stop channel switch command");
		goto out_free;
	}

out_free:
	kfree(cmd);

out:
	return ret;
}