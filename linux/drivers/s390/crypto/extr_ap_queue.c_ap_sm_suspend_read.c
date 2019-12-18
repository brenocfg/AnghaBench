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
struct ap_queue {int /*<<< orphan*/  queue_count; int /*<<< orphan*/  reply; } ;
typedef  enum ap_wait { ____Placeholder_ap_wait } ap_wait ;

/* Variables and functions */
#define  AP_RESPONSE_NORMAL 128 
 int AP_WAIT_AGAIN ; 
 int AP_WAIT_NONE ; 
 struct ap_queue_status ap_sm_recv (struct ap_queue*) ; 

__attribute__((used)) static enum ap_wait ap_sm_suspend_read(struct ap_queue *aq)
{
	struct ap_queue_status status;

	if (!aq->reply)
		return AP_WAIT_NONE;
	status = ap_sm_recv(aq);
	switch (status.response_code) {
	case AP_RESPONSE_NORMAL:
		if (aq->queue_count > 0)
			return AP_WAIT_AGAIN;
		/* fall through */
	default:
		return AP_WAIT_NONE;
	}
}