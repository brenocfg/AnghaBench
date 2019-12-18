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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct wiimote_data {TYPE_1__ state; int /*<<< orphan*/  rumble_worker; } ;
struct wiimod_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wiiproto_req_rumble (struct wiimote_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wiimod_rumble_remove(const struct wiimod_ops *ops,
				 struct wiimote_data *wdata)
{
	unsigned long flags;

	cancel_work_sync(&wdata->rumble_worker);

	spin_lock_irqsave(&wdata->state.lock, flags);
	wiiproto_req_rumble(wdata, 0);
	spin_unlock_irqrestore(&wdata->state.lock, flags);
}