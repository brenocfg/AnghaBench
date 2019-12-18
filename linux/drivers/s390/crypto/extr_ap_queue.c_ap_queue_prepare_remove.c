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
struct ap_queue {int /*<<< orphan*/  timeout; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_STATE_REMOVE ; 
 int /*<<< orphan*/  __ap_flush_queue (struct ap_queue*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ap_queue_prepare_remove(struct ap_queue *aq)
{
	spin_lock_bh(&aq->lock);
	/* flush queue */
	__ap_flush_queue(aq);
	/* set REMOVE state to prevent new messages are queued in */
	aq->state = AP_STATE_REMOVE;
	spin_unlock_bh(&aq->lock);
	del_timer_sync(&aq->timeout);
}