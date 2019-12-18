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
struct ap_queue {int /*<<< orphan*/  qid; } ;
struct ap_qirq_ctrl {int ir; int /*<<< orphan*/  isc; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_ISC ; 
 int /*<<< orphan*/  AP_QID_CARD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AP_QID_QUEUE (int /*<<< orphan*/ ) ; 
#define  AP_RESPONSE_BUSY 135 
#define  AP_RESPONSE_CHECKSTOPPED 134 
#define  AP_RESPONSE_DECONFIGURED 133 
#define  AP_RESPONSE_INVALID_ADDRESS 132 
#define  AP_RESPONSE_NORMAL 131 
#define  AP_RESPONSE_OTHERWISE_CHANGED 130 
#define  AP_RESPONSE_Q_NOT_AVAIL 129 
#define  AP_RESPONSE_RESET_IN_PROGRESS 128 
 int EBUSY ; 
 int EOPNOTSUPP ; 
 struct ap_queue_status ap_aqic (int /*<<< orphan*/ ,struct ap_qirq_ctrl,void*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ap_queue_enable_interruption(struct ap_queue *aq, void *ind)
{
	struct ap_queue_status status;
	struct ap_qirq_ctrl qirqctrl = { 0 };

	qirqctrl.ir = 1;
	qirqctrl.isc = AP_ISC;
	status = ap_aqic(aq->qid, qirqctrl, ind);
	switch (status.response_code) {
	case AP_RESPONSE_NORMAL:
	case AP_RESPONSE_OTHERWISE_CHANGED:
		return 0;
	case AP_RESPONSE_Q_NOT_AVAIL:
	case AP_RESPONSE_DECONFIGURED:
	case AP_RESPONSE_CHECKSTOPPED:
	case AP_RESPONSE_INVALID_ADDRESS:
		pr_err("Registering adapter interrupts for AP device %02x.%04x failed\n",
		       AP_QID_CARD(aq->qid),
		       AP_QID_QUEUE(aq->qid));
		return -EOPNOTSUPP;
	case AP_RESPONSE_RESET_IN_PROGRESS:
	case AP_RESPONSE_BUSY:
	default:
		return -EBUSY;
	}
}