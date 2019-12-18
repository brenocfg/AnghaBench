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
struct TYPE_2__ {int flags; int cmd_battery; } ;
struct wiimote_data {TYPE_1__ state; int /*<<< orphan*/  hdev; } ;
typedef  int __u8 ;

/* Variables and functions */
 int WIIPROTO_FLAG_EXT_ACTIVE ; 
 int WIIPROTO_FLAG_EXT_PLUGGED ; 
 int WIIPROTO_FLAG_MP_ACTIVE ; 
 int WIIPROTO_FLAG_MP_PLUGGED ; 
 int /*<<< orphan*/  WIIPROTO_REQ_SREQ ; 
 int /*<<< orphan*/  __wiimote_schedule (struct wiimote_data*) ; 
 int /*<<< orphan*/  handler_status_K (struct wiimote_data*,int const*) ; 
 int /*<<< orphan*/  hid_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wiimote_cmd_complete (struct wiimote_data*) ; 
 scalar_t__ wiimote_cmd_pending (struct wiimote_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handler_status(struct wiimote_data *wdata, const __u8 *payload)
{
	handler_status_K(wdata, payload);

	/* update extension status */
	if (payload[2] & 0x02) {
		if (!(wdata->state.flags & WIIPROTO_FLAG_EXT_PLUGGED)) {
			hid_dbg(wdata->hdev, "EXT hotplug: 1\n");
			wdata->state.flags |= WIIPROTO_FLAG_EXT_PLUGGED;
			__wiimote_schedule(wdata);
		}
	} else {
		if (wdata->state.flags & WIIPROTO_FLAG_EXT_PLUGGED) {
			hid_dbg(wdata->hdev, "EXT hotplug: 0\n");
			wdata->state.flags &= ~WIIPROTO_FLAG_EXT_PLUGGED;
			wdata->state.flags &= ~WIIPROTO_FLAG_MP_PLUGGED;
			wdata->state.flags &= ~WIIPROTO_FLAG_EXT_ACTIVE;
			wdata->state.flags &= ~WIIPROTO_FLAG_MP_ACTIVE;
			__wiimote_schedule(wdata);
		}
	}

	wdata->state.cmd_battery = payload[5];
	if (wiimote_cmd_pending(wdata, WIIPROTO_REQ_SREQ, 0))
		wiimote_cmd_complete(wdata);
}