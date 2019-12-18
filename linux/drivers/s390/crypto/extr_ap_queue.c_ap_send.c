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
typedef  int /*<<< orphan*/  ap_qid_t ;

/* Variables and functions */
#define  AP_RESPONSE_NORMAL 131 
#define  AP_RESPONSE_Q_FULL 130 
#define  AP_RESPONSE_REQ_FAC_NOT_INST 129 
#define  AP_RESPONSE_RESET_IN_PROGRESS 128 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 struct ap_queue_status __ap_send (int /*<<< orphan*/ ,unsigned long long,void*,size_t,int /*<<< orphan*/ ) ; 

int ap_send(ap_qid_t qid, unsigned long long psmid, void *msg, size_t length)
{
	struct ap_queue_status status;

	status = __ap_send(qid, psmid, msg, length, 0);
	switch (status.response_code) {
	case AP_RESPONSE_NORMAL:
		return 0;
	case AP_RESPONSE_Q_FULL:
	case AP_RESPONSE_RESET_IN_PROGRESS:
		return -EBUSY;
	case AP_RESPONSE_REQ_FAC_NOT_INST:
		return -EINVAL;
	default:	/* Device is gone. */
		return -ENODEV;
	}
}