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
struct ap_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  state; int /*<<< orphan*/  qid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_STATE_UNBOUND ; 
 int /*<<< orphan*/  ap_zapq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ap_queue_remove(struct ap_queue *aq)
{
	/*
	 * all messages have been flushed and the state is
	 * AP_STATE_REMOVE. Now reset with zero which also
	 * clears the irq registration and move the state
	 * to AP_STATE_UNBOUND to signal that this queue
	 * is not used by any driver currently.
	 */
	spin_lock_bh(&aq->lock);
	ap_zapq(aq->qid);
	aq->state = AP_STATE_UNBOUND;
	spin_unlock_bh(&aq->lock);
}