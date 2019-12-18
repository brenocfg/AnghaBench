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
struct wl12xx_cmd_start_fwlog {int dummy; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_START_FWLOGGER ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl12xx_cmd_start_fwlog*) ; 
 struct wl12xx_cmd_start_fwlog* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl12xx_cmd_start_fwlog*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 

int wl12xx_cmd_start_fwlog(struct wl1271 *wl)
{
	struct wl12xx_cmd_start_fwlog *cmd;
	int ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd start firmware logger");

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		ret = -ENOMEM;
		goto out;
	}

	ret = wl1271_cmd_send(wl, CMD_START_FWLOGGER, cmd, sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("failed to send start firmware logger command");
		goto out_free;
	}

out_free:
	kfree(cmd);

out:
	return ret;
}