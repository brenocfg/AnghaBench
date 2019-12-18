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
struct wl1251_cmd_trigger_scan_to {int /*<<< orphan*/  timeout; } ;
struct wl1251 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TRIGGER_SCAN_TO ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl1251_cmd_trigger_scan_to*) ; 
 struct wl1251_cmd_trigger_scan_to* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_send (struct wl1251*,int /*<<< orphan*/ ,struct wl1251_cmd_trigger_scan_to*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_error (char*,int) ; 

int wl1251_cmd_trigger_scan_to(struct wl1251 *wl, u32 timeout)
{
	struct wl1251_cmd_trigger_scan_to *cmd;
	int ret;

	wl1251_debug(DEBUG_CMD, "cmd trigger scan to");

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	cmd->timeout = timeout;

	ret = wl1251_cmd_send(wl, CMD_TRIGGER_SCAN_TO, cmd, sizeof(*cmd));
	if (ret < 0) {
		wl1251_error("cmd trigger scan to failed: %d", ret);
		goto out;
	}

out:
	kfree(cmd);
	return ret;
}