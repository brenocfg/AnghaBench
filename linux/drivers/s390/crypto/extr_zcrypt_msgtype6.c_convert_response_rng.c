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
struct type86x_reply {TYPE_3__ hdr; TYPE_1__ cprbx; } ;
struct ap_message {struct type86x_reply* message; } ;
struct TYPE_5__ {int /*<<< orphan*/  qid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_QID_CARD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AP_QID_QUEUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBF_ERR ; 
 int EAGAIN ; 
 int EINVAL ; 
#define  TYPE82_RSP_CODE 130 
#define  TYPE86_RSP_CODE 129 
#define  TYPE88_RSP_CODE 128 
 int /*<<< orphan*/  ZCRYPT_DBF (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int convert_type86_rng (struct zcrypt_queue*,struct ap_message*,char*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int convert_response_rng(struct zcrypt_queue *zq,
				 struct ap_message *reply,
				 char *data)
{
	struct type86x_reply *msg = reply->message;

	switch (msg->hdr.type) {
	case TYPE82_RSP_CODE:
	case TYPE88_RSP_CODE:
		return -EINVAL;
	case TYPE86_RSP_CODE:
		if (msg->hdr.reply_code)
			return -EINVAL;
		if (msg->cprbx.cprb_ver_id == 0x02)
			return convert_type86_rng(zq, reply, data);
		/* fall through - wrong cprb version is an unknown response */
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
		return -EAGAIN;	/* repeat the request on a different device. */
	}
}