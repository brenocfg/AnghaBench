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
struct wl18xx_cmd_dfs_master_restart {int /*<<< orphan*/  role_id; } ;
struct wl12xx_vif {int /*<<< orphan*/  role_id; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DFS_MASTER_RESTART ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl18xx_cmd_dfs_master_restart*) ; 
 struct wl18xx_cmd_dfs_master_restart* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl18xx_cmd_dfs_master_restart*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 

int wl18xx_cmd_dfs_master_restart(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	struct wl18xx_cmd_dfs_master_restart *cmd;
	int ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd dfs master restart (role %d)",
		     wlvif->role_id);

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	cmd->role_id = wlvif->role_id;

	ret = wl1271_cmd_send(wl, CMD_DFS_MASTER_RESTART,
			      cmd, sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("failed to send dfs master restart command");
		goto out_free;
	}
out_free:
	kfree(cmd);
	return ret;
}