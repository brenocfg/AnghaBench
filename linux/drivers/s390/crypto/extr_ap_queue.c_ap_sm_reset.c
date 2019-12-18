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
struct ap_queue {int /*<<< orphan*/  state; int /*<<< orphan*/  interrupt; int /*<<< orphan*/  qid; } ;
typedef  enum ap_wait { ____Placeholder_ap_wait } ap_wait ;

/* Variables and functions */
 int /*<<< orphan*/  AP_INTR_DISABLED ; 
#define  AP_RESPONSE_BUSY 133 
#define  AP_RESPONSE_CHECKSTOPPED 132 
#define  AP_RESPONSE_DECONFIGURED 131 
#define  AP_RESPONSE_NORMAL 130 
#define  AP_RESPONSE_Q_NOT_AVAIL 129 
#define  AP_RESPONSE_RESET_IN_PROGRESS 128 
 int /*<<< orphan*/  AP_STATE_BORKED ; 
 int /*<<< orphan*/  AP_STATE_RESET_WAIT ; 
 int AP_WAIT_NONE ; 
 int AP_WAIT_TIMEOUT ; 
 struct ap_queue_status ap_rapq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ap_wait ap_sm_reset(struct ap_queue *aq)
{
	struct ap_queue_status status;

	status = ap_rapq(aq->qid);
	switch (status.response_code) {
	case AP_RESPONSE_NORMAL:
	case AP_RESPONSE_RESET_IN_PROGRESS:
		aq->state = AP_STATE_RESET_WAIT;
		aq->interrupt = AP_INTR_DISABLED;
		return AP_WAIT_TIMEOUT;
	case AP_RESPONSE_BUSY:
		return AP_WAIT_TIMEOUT;
	case AP_RESPONSE_Q_NOT_AVAIL:
	case AP_RESPONSE_DECONFIGURED:
	case AP_RESPONSE_CHECKSTOPPED:
	default:
		aq->state = AP_STATE_BORKED;
		return AP_WAIT_NONE;
	}
}