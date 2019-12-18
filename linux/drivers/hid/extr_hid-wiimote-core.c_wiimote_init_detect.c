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
struct TYPE_2__ {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  devtype; } ;
struct wiimote_data {TYPE_1__ state; int /*<<< orphan*/  timer; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  WIIMOTE_DEV_UNKNOWN ; 
 int /*<<< orphan*/  WIIMOTE_EXT_NONE ; 
 int WIIPROTO_FLAG_BUILTIN_MP ; 
 int WIIPROTO_FLAG_EXT_PLUGGED ; 
 int WIIPROTO_FLAG_NO_MP ; 
 int /*<<< orphan*/  WIIPROTO_REQ_SREQ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiimote_cmd_acquire_noint (struct wiimote_data*) ; 
 int /*<<< orphan*/  wiimote_cmd_init_ext (struct wiimote_data*) ; 
 int /*<<< orphan*/  wiimote_cmd_read_ext (struct wiimote_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiimote_cmd_release (struct wiimote_data*) ; 
 int /*<<< orphan*/  wiimote_cmd_set (struct wiimote_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wiimote_cmd_wait_noint (struct wiimote_data*) ; 
 int /*<<< orphan*/  wiimote_init_set_type (struct wiimote_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiiproto_req_status (struct wiimote_data*) ; 

__attribute__((used)) static void wiimote_init_detect(struct wiimote_data *wdata)
{
	__u8 exttype = WIIMOTE_EXT_NONE, extdata[6];
	bool ext;
	int ret;

	wiimote_cmd_acquire_noint(wdata);

	spin_lock_irq(&wdata->state.lock);
	wdata->state.devtype = WIIMOTE_DEV_UNKNOWN;
	wiimote_cmd_set(wdata, WIIPROTO_REQ_SREQ, 0);
	wiiproto_req_status(wdata);
	spin_unlock_irq(&wdata->state.lock);

	ret = wiimote_cmd_wait_noint(wdata);
	if (ret)
		goto out_release;

	spin_lock_irq(&wdata->state.lock);
	ext = wdata->state.flags & WIIPROTO_FLAG_EXT_PLUGGED;
	spin_unlock_irq(&wdata->state.lock);

	if (!ext)
		goto out_release;

	wiimote_cmd_init_ext(wdata);
	exttype = wiimote_cmd_read_ext(wdata, extdata);

out_release:
	wiimote_cmd_release(wdata);
	wiimote_init_set_type(wdata, exttype);

	/* schedule MP timer */
	spin_lock_irq(&wdata->state.lock);
	if (!(wdata->state.flags & WIIPROTO_FLAG_BUILTIN_MP) &&
	    !(wdata->state.flags & WIIPROTO_FLAG_NO_MP))
		mod_timer(&wdata->timer, jiffies + HZ * 4);
	spin_unlock_irq(&wdata->state.lock);
}