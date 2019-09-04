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
struct wiimote_data {TYPE_1__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __wiimote_schedule (struct wiimote_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void wiimote_schedule(struct wiimote_data *wdata)
{
	unsigned long flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	__wiimote_schedule(wdata);
	spin_unlock_irqrestore(&wdata->state.lock, flags);
}