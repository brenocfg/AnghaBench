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
struct wl12xx_vif {scalar_t__ bss_type; int /*<<< orphan*/  role_id; int /*<<< orphan*/  flags; } ;
struct wl1271_cmd_sched_scan_start {int /*<<< orphan*/  tag; int /*<<< orphan*/  role_id; } ;
struct wl1271 {int quirks; } ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_STA_BSS ; 
 int /*<<< orphan*/  CMD_START_PERIODIC_SCAN ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int EBUSY ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WL1271_SCAN_DEFAULT_TAG ; 
 int WLCORE_QUIRK_NO_SCHED_SCAN_WHILE_CONN ; 
 int /*<<< orphan*/  WLVIF_FLAG_IN_USE ; 
 int /*<<< orphan*/  kfree (struct wl1271_cmd_sched_scan_start*) ; 
 struct wl1271_cmd_sched_scan_start* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl1271_cmd_sched_scan_start*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 

int wl1271_scan_sched_scan_start(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	struct wl1271_cmd_sched_scan_start *start;
	int ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd periodic scan start");

	if (wlvif->bss_type != BSS_TYPE_STA_BSS)
		return -EOPNOTSUPP;

	if ((wl->quirks & WLCORE_QUIRK_NO_SCHED_SCAN_WHILE_CONN) &&
	    test_bit(WLVIF_FLAG_IN_USE, &wlvif->flags))
		return -EBUSY;

	start = kzalloc(sizeof(*start), GFP_KERNEL);
	if (!start)
		return -ENOMEM;

	start->role_id = wlvif->role_id;
	start->tag = WL1271_SCAN_DEFAULT_TAG;

	ret = wl1271_cmd_send(wl, CMD_START_PERIODIC_SCAN, start,
			      sizeof(*start), 0);
	if (ret < 0) {
		wl1271_error("failed to send scan start command");
		goto out_free;
	}

out_free:
	kfree(start);
	return ret;
}