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
struct ap_queue_status {int response_code; } ;
struct ap_queue {scalar_t__ queue_count; int /*<<< orphan*/  state; int /*<<< orphan*/  qid; scalar_t__ reply; } ;
typedef  enum ap_wait { ____Placeholder_ap_wait } ap_wait ;

/* Variables and functions */
#define  AP_RESPONSE_BUSY 133 
#define  AP_RESPONSE_CHECKSTOPPED 132 
#define  AP_RESPONSE_DECONFIGURED 131 
#define  AP_RESPONSE_NORMAL 130 
#define  AP_RESPONSE_Q_NOT_AVAIL 129 
#define  AP_RESPONSE_RESET_IN_PROGRESS 128 
 int /*<<< orphan*/  AP_STATE_BORKED ; 
 int /*<<< orphan*/  AP_STATE_IDLE ; 
 int /*<<< orphan*/  AP_STATE_SETIRQ_WAIT ; 
 int /*<<< orphan*/  AP_STATE_WORKING ; 
 int AP_WAIT_AGAIN ; 
 int AP_WAIT_NONE ; 
 int AP_WAIT_TIMEOUT ; 
 void* ap_airq_ptr () ; 
 int /*<<< orphan*/  ap_queue_enable_interruption (struct ap_queue*,void*) ; 
 struct ap_queue_status ap_sm_recv (struct ap_queue*) ; 
 struct ap_queue_status ap_tapq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum ap_wait ap_sm_reset_wait(struct ap_queue *aq)
{
	struct ap_queue_status status;
	void *lsi_ptr;

	if (aq->queue_count > 0 && aq->reply)
		/* Try to read a completed message and get the status */
		status = ap_sm_recv(aq);
	else
		/* Get the status with TAPQ */
		status = ap_tapq(aq->qid, NULL);

	switch (status.response_code) {
	case AP_RESPONSE_NORMAL:
		lsi_ptr = ap_airq_ptr();
		if (lsi_ptr && ap_queue_enable_interruption(aq, lsi_ptr) == 0)
			aq->state = AP_STATE_SETIRQ_WAIT;
		else
			aq->state = (aq->queue_count > 0) ?
				AP_STATE_WORKING : AP_STATE_IDLE;
		return AP_WAIT_AGAIN;
	case AP_RESPONSE_BUSY:
	case AP_RESPONSE_RESET_IN_PROGRESS:
		return AP_WAIT_TIMEOUT;
	case AP_RESPONSE_Q_NOT_AVAIL:
	case AP_RESPONSE_DECONFIGURED:
	case AP_RESPONSE_CHECKSTOPPED:
	default:
		aq->state = AP_STATE_BORKED;
		return AP_WAIT_NONE;
	}
}