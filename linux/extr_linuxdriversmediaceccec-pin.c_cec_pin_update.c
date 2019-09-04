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
typedef  int u8 ;
struct cec_pin {int work_pin_events_dropped; int* work_pin_events; size_t work_pin_events_wr; int /*<<< orphan*/  kthread_waitq; int /*<<< orphan*/  work_pin_events_dropped_cnt; int /*<<< orphan*/  work_pin_num_events; int /*<<< orphan*/ * work_pin_ts; TYPE_1__* adap; } ;
struct TYPE_2__ {int cec_pin_is_high; } ;

/* Variables and functions */
 int CEC_NUM_PIN_EVENTS ; 
 int CEC_PIN_EVENT_FL_DROPPED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cec_pin_update(struct cec_pin *pin, bool v, bool force)
{
	if (!force && v == pin->adap->cec_pin_is_high)
		return;

	pin->adap->cec_pin_is_high = v;
	if (atomic_read(&pin->work_pin_num_events) < CEC_NUM_PIN_EVENTS) {
		u8 ev = v;

		if (pin->work_pin_events_dropped) {
			pin->work_pin_events_dropped = false;
			ev |= CEC_PIN_EVENT_FL_DROPPED;
		}
		pin->work_pin_events[pin->work_pin_events_wr] = ev;
		pin->work_pin_ts[pin->work_pin_events_wr] = ktime_get();
		pin->work_pin_events_wr =
			(pin->work_pin_events_wr + 1) % CEC_NUM_PIN_EVENTS;
		atomic_inc(&pin->work_pin_num_events);
	} else {
		pin->work_pin_events_dropped = true;
		pin->work_pin_events_dropped_cnt++;
	}
	wake_up_interruptible(&pin->kthread_waitq);
}