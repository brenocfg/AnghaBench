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
struct ap_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_EVENT_POLL ; 
 int /*<<< orphan*/  AP_STATE_RESET_START ; 
 int /*<<< orphan*/  ap_sm_event (struct ap_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ap_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ap_queue_reinit_state(struct ap_queue *aq)
{
	spin_lock_bh(&aq->lock);
	aq->state = AP_STATE_RESET_START;
	ap_wait(ap_sm_event(aq, AP_EVENT_POLL));
	spin_unlock_bh(&aq->lock);
}