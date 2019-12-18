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
struct msc_window {int lockout; int /*<<< orphan*/  lo_lock; TYPE_1__* msc; } ;
typedef  enum lockout_state { ____Placeholder_lockout_state } lockout_state ;
struct TYPE_2__ {int /*<<< orphan*/  user_count; int /*<<< orphan*/  mbuf; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int WIN_LOCKED ; 
 int WIN_READY ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  msc_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int msc_win_set_lockout(struct msc_window *win,
			       enum lockout_state expect,
			       enum lockout_state new)
{
	enum lockout_state old;
	unsigned long flags;
	int ret = 0;

	if (!win->msc->mbuf)
		return 0;

	spin_lock_irqsave(&win->lo_lock, flags);
	old = win->lockout;

	if (old != expect) {
		ret = -EINVAL;
		dev_warn_ratelimited(msc_dev(win->msc),
				     "expected lockout state %d, got %d\n",
				     expect, old);
		goto unlock;
	}

	win->lockout = new;

	if (old == expect && new == WIN_LOCKED)
		atomic_inc(&win->msc->user_count);
	else if (old == expect && old == WIN_LOCKED)
		atomic_dec(&win->msc->user_count);

unlock:
	spin_unlock_irqrestore(&win->lo_lock, flags);

	if (ret) {
		if (expect == WIN_READY && old == WIN_LOCKED)
			return -EBUSY;

		/* from intel_th_msc_window_unlock(), don't warn if not locked */
		if (expect == WIN_LOCKED && old == new)
			return 0;
	}

	return ret;
}