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
struct TYPE_2__ {int flags; size_t exttype; size_t devtype; } ;
struct wiimote_data {TYPE_1__ state; int /*<<< orphan*/  hdev; } ;
struct wiimod_ops {int /*<<< orphan*/  (* in_ext ) (struct wiimote_data*,int const*) ;int /*<<< orphan*/  (* in_mp ) (struct wiimote_data*,int const*) ;} ;
typedef  int __u8 ;

/* Variables and functions */
 int const WIIMOD_NULL ; 
 int WIIPROTO_FLAG_EXT_ACTIVE ; 
 int WIIPROTO_FLAG_MP_ACTIVE ; 
 int WIIPROTO_FLAG_MP_PLUGGED ; 
 int /*<<< orphan*/  __wiimote_schedule (struct wiimote_data*) ; 
 int /*<<< orphan*/  hid_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcmp (int const*,int const*,size_t) ; 
 int /*<<< orphan*/  stub1 (struct wiimote_data*,int const*) ; 
 int /*<<< orphan*/  stub2 (struct wiimote_data*,int const*) ; 
 int /*<<< orphan*/  stub3 (struct wiimote_data*,int const*) ; 
 int /*<<< orphan*/  stub4 (struct wiimote_data*,int const*) ; 
 int /*<<< orphan*/  stub5 (struct wiimote_data*,int const*) ; 
 int /*<<< orphan*/  stub6 (struct wiimote_data*,int const*) ; 
 scalar_t__ valid_ext_handler (struct wiimod_ops const*,size_t) ; 
 struct wiimod_ops** wiimod_ext_table ; 
 struct wiimod_ops wiimod_mp ; 
 struct wiimod_ops** wiimod_table ; 
 int** wiimote_devtype_mods ; 

__attribute__((used)) static void handler_ext(struct wiimote_data *wdata, const __u8 *payload,
			size_t len)
{
	static const __u8 invalid[21] = { 0xff, 0xff, 0xff, 0xff,
					  0xff, 0xff, 0xff, 0xff,
					  0xff, 0xff, 0xff, 0xff,
					  0xff, 0xff, 0xff, 0xff,
					  0xff, 0xff, 0xff, 0xff,
					  0xff };
	const __u8 *iter, *mods;
	const struct wiimod_ops *ops;
	bool is_mp;

	if (len > 21)
		len = 21;
	if (len < 6 || !memcmp(payload, invalid, len))
		return;

	/* if MP is active, track MP slot hotplugging */
	if (wdata->state.flags & WIIPROTO_FLAG_MP_ACTIVE) {
		/* this bit is set for invalid events (eg. during hotplug) */
		if (payload[5] & 0x01)
			return;

		if (payload[4] & 0x01) {
			if (!(wdata->state.flags & WIIPROTO_FLAG_MP_PLUGGED)) {
				hid_dbg(wdata->hdev, "MP hotplug: 1\n");
				wdata->state.flags |= WIIPROTO_FLAG_MP_PLUGGED;
				__wiimote_schedule(wdata);
			}
		} else {
			if (wdata->state.flags & WIIPROTO_FLAG_MP_PLUGGED) {
				hid_dbg(wdata->hdev, "MP hotplug: 0\n");
				wdata->state.flags &= ~WIIPROTO_FLAG_MP_PLUGGED;
				wdata->state.flags &= ~WIIPROTO_FLAG_EXT_ACTIVE;
				__wiimote_schedule(wdata);
			}
		}

		/* detect MP data that is sent interleaved with EXT data */
		is_mp = payload[5] & 0x02;
	} else {
		is_mp = false;
	}

	/* ignore EXT events if no extension is active */
	if (!(wdata->state.flags & WIIPROTO_FLAG_EXT_ACTIVE) && !is_mp)
		return;

	/* try forwarding to extension handler, first */
	ops = wiimod_ext_table[wdata->state.exttype];
	if (is_mp && ops->in_mp) {
		ops->in_mp(wdata, payload);
		return;
	} else if (!is_mp && valid_ext_handler(ops, len)) {
		ops->in_ext(wdata, payload);
		return;
	}

	/* try forwarding to MP handler */
	ops = &wiimod_mp;
	if (is_mp && ops->in_mp) {
		ops->in_mp(wdata, payload);
		return;
	} else if (!is_mp && valid_ext_handler(ops, len)) {
		ops->in_ext(wdata, payload);
		return;
	}

	/* try forwarding to loaded modules */
	mods = wiimote_devtype_mods[wdata->state.devtype];
	for (iter = mods; *iter != WIIMOD_NULL; ++iter) {
		ops = wiimod_table[*iter];
		if (is_mp && ops->in_mp) {
			ops->in_mp(wdata, payload);
			return;
		} else if (!is_mp && valid_ext_handler(ops, len)) {
			ops->in_ext(wdata, payload);
			return;
		}
	}
}