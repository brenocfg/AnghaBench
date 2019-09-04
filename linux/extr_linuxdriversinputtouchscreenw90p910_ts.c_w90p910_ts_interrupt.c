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
struct w90p910_ts {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
#define  TS_IDLE 131 
#define  TS_WAIT_NEW_PACKET 130 
#define  TS_WAIT_X_COORD 129 
#define  TS_WAIT_Y_COORD 128 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  w90p910_prepare_next_packet (struct w90p910_ts*) ; 
 int /*<<< orphan*/  w90p910_prepare_x_reading (struct w90p910_ts*) ; 
 int /*<<< orphan*/  w90p910_prepare_y_reading (struct w90p910_ts*) ; 
 int /*<<< orphan*/  w90p910_report_event (struct w90p910_ts*,int) ; 

__attribute__((used)) static irqreturn_t w90p910_ts_interrupt(int irq, void *dev_id)
{
	struct w90p910_ts *w90p910_ts = dev_id;
	unsigned long flags;

	spin_lock_irqsave(&w90p910_ts->lock, flags);

	switch (w90p910_ts->state) {
	case TS_WAIT_NEW_PACKET:
		/*
		 * The controller only generates interrupts when pen
		 * is down.
		 */
		del_timer(&w90p910_ts->timer);
		w90p910_prepare_x_reading(w90p910_ts);
		break;


	case TS_WAIT_X_COORD:
		w90p910_prepare_y_reading(w90p910_ts);
		break;

	case TS_WAIT_Y_COORD:
		w90p910_report_event(w90p910_ts, true);
		w90p910_prepare_next_packet(w90p910_ts);
		mod_timer(&w90p910_ts->timer, jiffies + msecs_to_jiffies(100));
		break;

	case TS_IDLE:
		break;
	}

	spin_unlock_irqrestore(&w90p910_ts->lock, flags);

	return IRQ_HANDLED;
}