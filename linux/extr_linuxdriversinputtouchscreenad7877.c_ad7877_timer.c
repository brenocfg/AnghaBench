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
struct timer_list {int dummy; } ;
struct ad7877 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad7877_ts_event_release (struct ad7877*) ; 
 struct ad7877* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 
 struct ad7877* ts ; 

__attribute__((used)) static void ad7877_timer(struct timer_list *t)
{
	struct ad7877 *ts = from_timer(ts, t, timer);
	unsigned long flags;

	spin_lock_irqsave(&ts->lock, flags);
	ad7877_ts_event_release(ts);
	spin_unlock_irqrestore(&ts->lock, flags);
}