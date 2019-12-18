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
struct timer_list {int dummy; } ;
struct TYPE_2__ {scalar_t__ expires; } ;
struct raw3215_info {int flags; int /*<<< orphan*/  cdev; TYPE_1__ timer; scalar_t__ queued_write; scalar_t__ queued_read; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 scalar_t__ RAW3215_TIMEOUT ; 
 int RAW3215_TIMER_RUNS ; 
 int RAW3215_WORKING ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 struct raw3215_info* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 struct raw3215_info* raw ; 
 int /*<<< orphan*/  raw3215_mk_write_req (struct raw3215_info*) ; 
 int /*<<< orphan*/  raw3215_start_io (struct raw3215_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  tty_port_suspended (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raw3215_timeout(struct timer_list *t)
{
	struct raw3215_info *raw = from_timer(raw, t, timer);
	unsigned long flags;

	spin_lock_irqsave(get_ccwdev_lock(raw->cdev), flags);
	raw->flags &= ~RAW3215_TIMER_RUNS;
	if (!tty_port_suspended(&raw->port)) {
		raw3215_mk_write_req(raw);
		raw3215_start_io(raw);
		if ((raw->queued_read || raw->queued_write) &&
		    !(raw->flags & RAW3215_WORKING) &&
		    !(raw->flags & RAW3215_TIMER_RUNS)) {
			raw->timer.expires = RAW3215_TIMEOUT + jiffies;
			add_timer(&raw->timer);
			raw->flags |= RAW3215_TIMER_RUNS;
		}
	}
	spin_unlock_irqrestore(get_ccwdev_lock(raw->cdev), flags);
}