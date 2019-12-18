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
typedef  int /*<<< orphan*/  u8 ;
struct wl18xx_cmd_scan_stop {int /*<<< orphan*/  scan_type; int /*<<< orphan*/  role_id; } ;
struct wl12xx_vif {int /*<<< orphan*/  role_id; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_STOP_SCAN ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl18xx_cmd_scan_stop*) ; 
 struct wl18xx_cmd_scan_stop* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl18xx_cmd_scan_stop*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 

__attribute__((used)) static int __wl18xx_scan_stop(struct wl1271 *wl, struct wl12xx_vif *wlvif,
			       u8 scan_type)
{
	struct wl18xx_cmd_scan_stop *stop;
	int ret;

	wl1271_debug(DEBUG_CMD, "cmd periodic scan stop");

	stop = kzalloc(sizeof(*stop), GFP_KERNEL);
	if (!stop) {
		wl1271_error("failed to alloc memory to send sched scan stop");
		return -ENOMEM;
	}

	stop->role_id = wlvif->role_id;
	stop->scan_type = scan_type;

	ret = wl1271_cmd_send(wl, CMD_STOP_SCAN, stop, sizeof(*stop), 0);
	if (ret < 0) {
		wl1271_error("failed to send sched scan stop command");
		goto out_free;
	}

out_free:
	kfree(stop);
	return ret;
}