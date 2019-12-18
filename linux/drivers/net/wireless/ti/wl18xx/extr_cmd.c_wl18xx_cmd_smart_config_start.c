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
typedef  int /*<<< orphan*/  u32 ;
struct wl18xx_cmd_smart_config_start {int /*<<< orphan*/  group_id_bitmask; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SMART_CONFIG_START ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wl18xx_cmd_smart_config_start*) ; 
 struct wl18xx_cmd_smart_config_start* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl18xx_cmd_smart_config_start*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 

int wl18xx_cmd_smart_config_start(struct wl1271 *wl, u32 group_bitmap)
{
	struct wl18xx_cmd_smart_config_start *cmd;
	int ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd smart config start group_bitmap=0x%x",
		     group_bitmap);

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		ret = -ENOMEM;
		goto out;
	}

	cmd->group_id_bitmask = cpu_to_le32(group_bitmap);

	ret = wl1271_cmd_send(wl, CMD_SMART_CONFIG_START, cmd, sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("failed to send smart config start command");
		goto out_free;
	}

out_free:
	kfree(cmd);
out:
	return ret;
}