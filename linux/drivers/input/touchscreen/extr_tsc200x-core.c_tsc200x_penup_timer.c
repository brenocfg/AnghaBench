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
struct tsc200x {int /*<<< orphan*/  lock; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 struct tsc200x* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  penup_timer ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct tsc200x* ts ; 
 int /*<<< orphan*/  tsc200x_update_pen_state (struct tsc200x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tsc200x_penup_timer(struct timer_list *t)
{
	struct tsc200x *ts = from_timer(ts, t, penup_timer);
	unsigned long flags;

	spin_lock_irqsave(&ts->lock, flags);
	tsc200x_update_pen_state(ts, 0, 0, 0);
	spin_unlock_irqrestore(&ts->lock, flags);
}