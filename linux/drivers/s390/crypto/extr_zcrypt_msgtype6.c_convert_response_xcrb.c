#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct zcrypt_queue {TYPE_3__* queue; int /*<<< orphan*/  online; } ;
struct TYPE_8__ {int type; int /*<<< orphan*/  reply_code; } ;
struct TYPE_6__ {int cprb_ver_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  apfs; } ;
struct type86x_reply {TYPE_4__ hdr; TYPE_2__ cprbx; TYPE_1__ fmt2; } ;
struct ica_xcRB {int status; } ;
struct ap_message {struct type86x_reply* message; } ;
struct TYPE_7__ {int /*<<< orphan*/  qid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_QID_CARD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AP_QID_QUEUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBF_ERR ; 
 int EAGAIN ; 
#define  TYPE82_RSP_CODE 130 
#define  TYPE86_RSP_CODE 129 
#define  TYPE88_RSP_CODE 128 
 int /*<<< orphan*/  ZCRYPT_DBF (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int convert_error (struct zcrypt_queue*,struct ap_message*) ; 
 int convert_type86_xcrb (struct zcrypt_queue*,struct ap_message*,struct ica_xcRB*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int convert_response_xcrb(struct zcrypt_queue *zq,
			    struct ap_message *reply,
			    struct ica_xcRB *xcRB)
{
	struct type86x_reply *msg = reply->message;

	switch (msg->hdr.type) {
	case TYPE82_RSP_CODE:
	case TYPE88_RSP_CODE:
		xcRB->status = 0x0008044DL; /* HDD_InvalidParm */
		return convert_error(zq, reply);
	case TYPE86_RSP_CODE:
		if (msg->hdr.reply_code) {
			memcpy(&(xcRB->status), msg->fmt2.apfs, sizeof(u32));
			return convert_error(zq, reply);
		}
		if (msg->cprbx.cprb_ver_id == 0x02)
			return convert_type86_xcrb(zq, reply, xcRB);
		/* fall through - wrong cprb version is an unknown response */
	default: /* Unknown response type, this should NEVER EVER happen */
		xcRB->status = 0x0008044DL; /* HDD_InvalidParm */
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