#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ucb1x00_ts {int /*<<< orphan*/ * rtask; int /*<<< orphan*/  irq_wait; TYPE_1__* ucb; int /*<<< orphan*/  irq_lock; scalar_t__ irq_disabled; } ;
struct TYPE_5__ {scalar_t__ irq_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HZ ; 
 long MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 scalar_t__ UCB_IRQ_TSPX ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  enable_irq (scalar_t__) ; 
 int /*<<< orphan*/  kthread_freezable_should_stop (int*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout (long) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucb1x00_adc_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  ucb1x00_adc_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  ucb1x00_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  ucb1x00_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  ucb1x00_ts_event_release (struct ucb1x00_ts*) ; 
 int /*<<< orphan*/  ucb1x00_ts_evt_add (struct ucb1x00_ts*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ucb1x00_ts_mode_int (struct ucb1x00_ts*) ; 
 scalar_t__ ucb1x00_ts_pen_down (struct ucb1x00_ts*) ; 
 unsigned int ucb1x00_ts_read_pressure (struct ucb1x00_ts*) ; 
 unsigned int ucb1x00_ts_read_xpos (struct ucb1x00_ts*) ; 
 unsigned int ucb1x00_ts_read_ypos (struct ucb1x00_ts*) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int ucb1x00_thread(void *_ts)
{
	struct ucb1x00_ts *ts = _ts;
	DECLARE_WAITQUEUE(wait, current);
	bool frozen, ignore = false;
	int valid = 0;

	set_freezable();
	add_wait_queue(&ts->irq_wait, &wait);
	while (!kthread_freezable_should_stop(&frozen)) {
		unsigned int x, y, p;
		signed long timeout;

		if (frozen)
			ignore = true;

		ucb1x00_adc_enable(ts->ucb);

		x = ucb1x00_ts_read_xpos(ts);
		y = ucb1x00_ts_read_ypos(ts);
		p = ucb1x00_ts_read_pressure(ts);

		/*
		 * Switch back to interrupt mode.
		 */
		ucb1x00_ts_mode_int(ts);
		ucb1x00_adc_disable(ts->ucb);

		msleep(10);

		ucb1x00_enable(ts->ucb);


		if (ucb1x00_ts_pen_down(ts)) {
			set_current_state(TASK_INTERRUPTIBLE);

			spin_lock_irq(&ts->irq_lock);
			if (ts->irq_disabled) {
				ts->irq_disabled = 0;
				enable_irq(ts->ucb->irq_base + UCB_IRQ_TSPX);
			}
			spin_unlock_irq(&ts->irq_lock);
			ucb1x00_disable(ts->ucb);

			/*
			 * If we spat out a valid sample set last time,
			 * spit out a "pen off" sample here.
			 */
			if (valid) {
				ucb1x00_ts_event_release(ts);
				valid = 0;
			}

			timeout = MAX_SCHEDULE_TIMEOUT;
		} else {
			ucb1x00_disable(ts->ucb);

			/*
			 * Filtering is policy.  Policy belongs in user
			 * space.  We therefore leave it to user space
			 * to do any filtering they please.
			 */
			if (!ignore) {
				ucb1x00_ts_evt_add(ts, p, x, y);
				valid = 1;
			}

			set_current_state(TASK_INTERRUPTIBLE);
			timeout = HZ / 100;
		}

		schedule_timeout(timeout);
	}

	remove_wait_queue(&ts->irq_wait, &wait);

	ts->rtask = NULL;
	return 0;
}