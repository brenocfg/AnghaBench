#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct zcrypt_queue {TYPE_2__* queue; int /*<<< orphan*/  online; } ;
struct TYPE_6__ {int type; int /*<<< orphan*/  reply_code; } ;
struct TYPE_4__ {int cprb_ver_id; } ;
struct type86_ep11_reply {TYPE_3__ hdr; TYPE_1__ cprbx; } ;
struct ep11_urb {int dummy; } ;
struct ap_message {struct type86_ep11_reply* message; } ;
struct TYPE_5__ {int /*<<< orphan*/  qid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_QID_CARD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AP_QID_QUEUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBF_ERR ; 
 int EAGAIN ; 
#define  TYPE82_RSP_CODE 130 
#define  TYPE86_RSP_CODE 129 
#define  TYPE87_RSP_CODE 128 
 int /*<<< orphan*/  ZCRYPT_DBF (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int convert_error (struct zcrypt_queue*,struct ap_message*) ; 
 int convert_type86_ep11_xcrb (struct zcrypt_queue*,struct ap_message*,struct ep11_urb*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int convert_response_ep11_xcrb(struct zcrypt_queue *zq,
	struct ap_message *reply, struct ep11_urb *xcRB)
{
	struct type86_ep11_reply *msg = reply->message;

	switch (msg->hdr.type) {
	case TYPE82_RSP_CODE:
	case TYPE87_RSP_CODE:
		return convert_error(zq, reply);
	case TYPE86_RSP_CODE:
		if (msg->hdr.reply_code)
			return convert_error(zq, reply);
		if (msg->cprbx.cprb_ver_id == 0x04)
			return convert_type86_ep11_xcrb(zq, reply, xcRB);
		/* fall through - wrong cprb version is an unknown resp */
	default: /* Unknown response type, this should NEVER EVER happen */
		zq->online = 0;
		pr_err("Cryptographic device %02x.%04x failed and was set offline\n",
		       AP_QID_CARD(zq->queue->qid),
		       AP_QID_QUEUE(zq->queue->qid));
		ZCRYPT_DBF(DBF_ERR,
			   "device=%02x.%04x rtype=0x%02x => online=0 rc=EAGAIN\n",
			   AP_QID_CARD(zq->queue->qid),
			   AP_QID_QUEUE(zq->queue->qid),
			   (int) msg->hdr.type);
		return -EAGAIN; /* repeat the request on a different device. */
	}
}