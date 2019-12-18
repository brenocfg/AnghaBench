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
struct ap_queue_status {int irq_enabled; int response_code; } ;
struct ap_queue {scalar_t__ queue_count; int /*<<< orphan*/  state; int /*<<< orphan*/  interrupt; int /*<<< orphan*/  qid; scalar_t__ reply; } ;
typedef  enum ap_wait { ____Placeholder_ap_wait } ap_wait ;

/* Variables and functions */
 int /*<<< orphan*/  AP_INTR_ENABLED ; 
#define  AP_RESPONSE_NORMAL 129 
#define  AP_RESPONSE_NO_PENDING_REPLY 128 
 int /*<<< orphan*/  AP_STATE_BORKED ; 
 int /*<<< orphan*/  AP_STATE_IDLE ; 
 int /*<<< orphan*/  AP_STATE_WORKING ; 
 int AP_WAIT_AGAIN ; 
 int AP_WAIT_NONE ; 
 int AP_WAIT_TIMEOUT ; 
 struct ap_queue_status ap_sm_recv (struct ap_queue*) ; 
 struct ap_queue_status ap_tapq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum ap_wait ap_sm_setirq_wait(struct ap_queue *aq)
{
	struct ap_queue_status status;

	if (aq->queue_count > 0 && aq->reply)
		/* Try to read a completed message and get the status */
		status = ap_sm_recv(aq);
	else
		/* Get the status with TAPQ */
		status = ap_tapq(aq->qid, NULL);

	if (status.irq_enabled == 1) {
		/* Irqs are now enabled */
		aq->interrupt = AP_INTR_ENABLED;
		aq->state = (aq->queue_count > 0) ?
			AP_STATE_WORKING : AP_STATE_IDLE;
	}

	switch (status.response_code) {
	case AP_RESPONSE_NORMAL:
		if (aq->queue_count > 0)
			return AP_WAIT_AGAIN;
		/* fallthrough */
	case AP_RESPONSE_NO_PENDING_REPLY:
		return AP_WAIT_TIMEOUT;
	default:
		aq->state = AP_STATE_BORKED;
		return AP_WAIT_NONE;
	}
}