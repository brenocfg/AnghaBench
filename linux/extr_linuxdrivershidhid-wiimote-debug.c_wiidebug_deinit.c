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
struct wiimote_debug {int /*<<< orphan*/  eeprom; int /*<<< orphan*/  drm; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct wiimote_data {TYPE_1__ state; struct wiimote_debug* debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wiimote_debug*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void wiidebug_deinit(struct wiimote_data *wdata)
{
	struct wiimote_debug *dbg = wdata->debug;
	unsigned long flags;

	if (!dbg)
		return;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->debug = NULL;
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	debugfs_remove(dbg->drm);
	debugfs_remove(dbg->eeprom);
	kfree(dbg);
}