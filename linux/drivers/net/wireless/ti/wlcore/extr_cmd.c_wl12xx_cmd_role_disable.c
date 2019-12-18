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
typedef  scalar_t__ u8 ;
struct wl12xx_cmd_role_disable {scalar_t__ role_id; } ;
struct wl1271 {int /*<<< orphan*/  roles_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ROLE_DISABLE ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WL12XX_INVALID_ROLE_ID ; 
 int /*<<< orphan*/  __clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wl12xx_cmd_role_disable*) ; 
 struct wl12xx_cmd_role_disable* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl12xx_cmd_role_disable*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 

int wl12xx_cmd_role_disable(struct wl1271 *wl, u8 *role_id)
{
	struct wl12xx_cmd_role_disable *cmd;
	int ret;

	wl1271_debug(DEBUG_CMD, "cmd role disable");

	if (WARN_ON(*role_id == WL12XX_INVALID_ROLE_ID))
		return -ENOENT;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		ret = -ENOMEM;
		goto out;
	}
	cmd->role_id = *role_id;

	ret = wl1271_cmd_send(wl, CMD_ROLE_DISABLE, cmd, sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("failed to initiate cmd role disable");
		goto out_free;
	}

	__clear_bit(*role_id, wl->roles_map);
	*role_id = WL12XX_INVALID_ROLE_ID;

out_free:
	kfree(cmd);

out:
	return ret;
}