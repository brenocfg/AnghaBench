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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wl18xx_cmd_smart_config_set_group_key {int /*<<< orphan*/  key; int /*<<< orphan*/  group_id; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SMART_CONFIG_SET_GROUP_KEY ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int E2BIG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wl18xx_cmd_smart_config_set_group_key*) ; 
 struct wl18xx_cmd_smart_config_set_group_key* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl18xx_cmd_smart_config_set_group_key*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_error (char*,...) ; 

int wl18xx_cmd_smart_config_set_group_key(struct wl1271 *wl, u16 group_id,
					  u8 key_len, u8 *key)
{
	struct wl18xx_cmd_smart_config_set_group_key *cmd;
	int ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd smart config set group key id=0x%x",
		     group_id);

	if (key_len != sizeof(cmd->key)) {
		wl1271_error("invalid group key size: %d", key_len);
		return -E2BIG;
	}

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		ret = -ENOMEM;
		goto out;
	}

	cmd->group_id = cpu_to_le32(group_id);
	memcpy(cmd->key, key, key_len);

	ret = wl1271_cmd_send(wl, CMD_SMART_CONFIG_SET_GROUP_KEY, cmd,
			      sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("failed to send smart config set group key cmd");
		goto out_free;
	}

out_free:
	kfree(cmd);
out:
	return ret;
}