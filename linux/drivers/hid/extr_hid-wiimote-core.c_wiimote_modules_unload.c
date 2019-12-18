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
struct TYPE_2__ {size_t devtype; int /*<<< orphan*/  lock; } ;
struct wiimote_data {int /*<<< orphan*/ * input; TYPE_1__ state; } ;
struct wiimod_ops {int /*<<< orphan*/  (* remove ) (struct wiimod_ops const*,struct wiimote_data*) ;} ;
typedef  size_t __u8 ;

/* Variables and functions */
 size_t const WIIMOD_NULL ; 
 size_t WIIMOTE_DEV_UNKNOWN ; 
 int /*<<< orphan*/  input_get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct wiimod_ops const*,struct wiimote_data*) ; 
 struct wiimod_ops** wiimod_table ; 
 size_t** wiimote_devtype_mods ; 

__attribute__((used)) static void wiimote_modules_unload(struct wiimote_data *wdata)
{
	const __u8 *mods, *iter;
	const struct wiimod_ops *ops;
	unsigned long flags;

	mods = wiimote_devtype_mods[wdata->state.devtype];

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.devtype = WIIMOTE_DEV_UNKNOWN;
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	/* find end of list */
	for (iter = mods; *iter != WIIMOD_NULL; ++iter)
		/* empty */ ;

	if (wdata->input) {
		input_get_device(wdata->input);
		input_unregister_device(wdata->input);
	}

	for ( ; iter-- != mods; ) {
		ops = wiimod_table[*iter];
		if (ops->remove)
			ops->remove(ops, wdata);
	}

	if (wdata->input) {
		input_put_device(wdata->input);
		wdata->input = NULL;
	}
}