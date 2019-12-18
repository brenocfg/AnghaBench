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
struct TYPE_2__ {int flags; size_t exttype; int mp; int /*<<< orphan*/  lock; } ;
struct wiimote_data {TYPE_1__ state; int /*<<< orphan*/  hdev; int /*<<< orphan*/  timer; } ;
typedef  size_t __u8 ;
typedef  int __u32 ;

/* Variables and functions */
 int HZ ; 
 size_t WIIMOTE_EXT_NONE ; 
 size_t WIIMOTE_EXT_UNKNOWN ; 
 int WIIPROTO_FLAG_BUILTIN_MP ; 
 int WIIPROTO_FLAG_EXT_ACTIVE ; 
 int WIIPROTO_FLAG_EXT_PLUGGED ; 
 int WIIPROTO_FLAG_MP_ACTIVE ; 
 int WIIPROTO_FLAG_MP_PLUGGED ; 
 int WIIPROTO_FLAG_MP_USED ; 
 int WIIPROTO_FLAG_NO_MP ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hid_info (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiimote_cmd_acquire_noint (struct wiimote_data*) ; 
 int /*<<< orphan*/  wiimote_cmd_init_ext (struct wiimote_data*) ; 
 int /*<<< orphan*/  wiimote_cmd_init_mp (struct wiimote_data*) ; 
 int /*<<< orphan*/  wiimote_cmd_map_mp (struct wiimote_data*,size_t) ; 
 size_t wiimote_cmd_read_ext (struct wiimote_data*,size_t*) ; 
 int wiimote_cmd_read_mp (struct wiimote_data*,size_t*) ; 
 int /*<<< orphan*/  wiimote_cmd_release (struct wiimote_data*) ; 
 int /*<<< orphan*/  wiimote_ext_load (struct wiimote_data*,size_t) ; 
 int /*<<< orphan*/  wiimote_ext_unload (struct wiimote_data*) ; 
 int /*<<< orphan*/ * wiimote_exttype_names ; 
 int /*<<< orphan*/  wiimote_mp_load (struct wiimote_data*) ; 
 int /*<<< orphan*/  wiimote_mp_unload (struct wiimote_data*) ; 
 int /*<<< orphan*/  wiiproto_req_status (struct wiimote_data*) ; 

__attribute__((used)) static void wiimote_init_hotplug(struct wiimote_data *wdata)
{
	__u8 exttype, extdata[6], mpdata[6];
	__u32 flags;
	bool mp;

	hid_dbg(wdata->hdev, "detect extensions..\n");

	wiimote_cmd_acquire_noint(wdata);

	spin_lock_irq(&wdata->state.lock);

	/* get state snapshot that we will then work on */
	flags = wdata->state.flags;

	/* disable event forwarding temporarily */
	wdata->state.flags &= ~WIIPROTO_FLAG_EXT_ACTIVE;
	wdata->state.flags &= ~WIIPROTO_FLAG_MP_ACTIVE;

	spin_unlock_irq(&wdata->state.lock);

	/* init extension and MP (deactivates current extension or MP) */
	wiimote_cmd_init_ext(wdata);
	if (flags & WIIPROTO_FLAG_NO_MP) {
		mp = false;
	} else {
		wiimote_cmd_init_mp(wdata);
		mp = wiimote_cmd_read_mp(wdata, mpdata);
	}
	exttype = wiimote_cmd_read_ext(wdata, extdata);

	wiimote_cmd_release(wdata);

	/* load/unload extension module if it changed */
	if (exttype != wdata->state.exttype) {
		/* unload previous extension */
		wiimote_ext_unload(wdata);

		if (exttype == WIIMOTE_EXT_UNKNOWN) {
			hid_info(wdata->hdev, "cannot detect extension; %6phC\n",
				 extdata);
		} else if (exttype == WIIMOTE_EXT_NONE) {
			spin_lock_irq(&wdata->state.lock);
			wdata->state.exttype = WIIMOTE_EXT_NONE;
			spin_unlock_irq(&wdata->state.lock);
		} else {
			hid_info(wdata->hdev, "detected extension: %s\n",
				 wiimote_exttype_names[exttype]);
			/* try loading new extension */
			wiimote_ext_load(wdata, exttype);
		}
	}

	/* load/unload MP module if it changed */
	if (mp) {
		if (!wdata->state.mp) {
			hid_info(wdata->hdev, "detected extension: Nintendo Wii Motion Plus\n");
			wiimote_mp_load(wdata);
		}
	} else if (wdata->state.mp) {
		wiimote_mp_unload(wdata);
	}

	/* if MP is not used, do not map or activate it */
	if (!(flags & WIIPROTO_FLAG_MP_USED))
		mp = false;

	/* map MP into main extension registers if used */
	if (mp) {
		wiimote_cmd_acquire_noint(wdata);
		wiimote_cmd_map_mp(wdata, exttype);
		wiimote_cmd_release(wdata);

		/* delete MP hotplug timer */
		del_timer_sync(&wdata->timer);
	} else {
		/* reschedule MP hotplug timer */
		if (!(flags & WIIPROTO_FLAG_BUILTIN_MP) &&
		    !(flags & WIIPROTO_FLAG_NO_MP))
			mod_timer(&wdata->timer, jiffies + HZ * 4);
	}

	spin_lock_irq(&wdata->state.lock);

	/* enable data forwarding again and set expected hotplug state */
	if (mp) {
		wdata->state.flags |= WIIPROTO_FLAG_MP_ACTIVE;
		if (wdata->state.exttype == WIIMOTE_EXT_NONE) {
			wdata->state.flags &= ~WIIPROTO_FLAG_EXT_PLUGGED;
			wdata->state.flags &= ~WIIPROTO_FLAG_MP_PLUGGED;
		} else {
			wdata->state.flags &= ~WIIPROTO_FLAG_EXT_PLUGGED;
			wdata->state.flags |= WIIPROTO_FLAG_MP_PLUGGED;
			wdata->state.flags |= WIIPROTO_FLAG_EXT_ACTIVE;
		}
	} else if (wdata->state.exttype != WIIMOTE_EXT_NONE) {
		wdata->state.flags |= WIIPROTO_FLAG_EXT_ACTIVE;
	}

	/* request status report for hotplug state updates */
	wiiproto_req_status(wdata);

	spin_unlock_irq(&wdata->state.lock);

	hid_dbg(wdata->hdev, "detected extensions: MP: %d EXT: %d\n",
		wdata->state.mp, wdata->state.exttype);
}