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
struct TYPE_2__ {scalar_t__ hlid; } ;
struct wl12xx_vif {TYPE_1__ sta; int /*<<< orphan*/  role_id; } ;
struct wl12xx_cmd_role_stop {int /*<<< orphan*/  reason; int /*<<< orphan*/  disc_type; int /*<<< orphan*/  role_id; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ROLE_STOP ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int /*<<< orphan*/  DISCONNECT_IMMEDIATE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WL12XX_INVALID_LINK_ID ; 
 int /*<<< orphan*/  WLAN_REASON_UNSPECIFIED ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wl12xx_cmd_role_stop*) ; 
 struct wl12xx_cmd_role_stop* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl12xx_cmd_role_stop*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 
 int /*<<< orphan*/  wl12xx_free_link (struct wl1271*,struct wl12xx_vif*,scalar_t__*) ; 

int wl12xx_cmd_role_stop_sta(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	struct wl12xx_cmd_role_stop *cmd;
	int ret;

	if (WARN_ON(wlvif->sta.hlid == WL12XX_INVALID_LINK_ID))
		return -EINVAL;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		ret = -ENOMEM;
		goto out;
	}

	wl1271_debug(DEBUG_CMD, "cmd role stop sta %d", wlvif->role_id);

	cmd->role_id = wlvif->role_id;
	cmd->disc_type = DISCONNECT_IMMEDIATE;
	cmd->reason = cpu_to_le16(WLAN_REASON_UNSPECIFIED);

	ret = wl1271_cmd_send(wl, CMD_ROLE_STOP, cmd, sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("failed to initiate cmd role stop sta");
		goto out_free;
	}

	wl12xx_free_link(wl, wlvif, &wlvif->sta.hlid);

out_free:
	kfree(cmd);

out:
	return ret;
}