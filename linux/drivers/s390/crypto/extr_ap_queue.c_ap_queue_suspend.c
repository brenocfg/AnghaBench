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
struct ap_device {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_EVENT_POLL ; 
 int /*<<< orphan*/  AP_STATE_BORKED ; 
 int /*<<< orphan*/  AP_STATE_SUSPEND_WAIT ; 
 scalar_t__ AP_WAIT_NONE ; 
 scalar_t__ ap_sm_event (struct ap_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct ap_queue* to_ap_queue (int /*<<< orphan*/ *) ; 

void ap_queue_suspend(struct ap_device *ap_dev)
{
	struct ap_queue *aq = to_ap_queue(&ap_dev->device);

	/* Poll on the device until all requests are finished. */
	spin_lock_bh(&aq->lock);
	aq->state = AP_STATE_SUSPEND_WAIT;
	while (ap_sm_event(aq, AP_EVENT_POLL) != AP_WAIT_NONE)
		;
	aq->state = AP_STATE_BORKED;
	spin_unlock_bh(&aq->lock);
}