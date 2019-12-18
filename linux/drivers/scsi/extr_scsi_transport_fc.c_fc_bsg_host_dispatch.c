#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct fc_internal {TYPE_6__* f; } ;
struct TYPE_9__ {long vendor_id; } ;
struct TYPE_10__ {TYPE_3__ h_vendor; } ;
struct fc_bsg_request {int msgcode; TYPE_4__ rqst_data; } ;
struct fc_bsg_reply {int result; scalar_t__ reply_payload_rcv_len; } ;
struct fc_bsg_host_vendor {int dummy; } ;
struct fc_bsg_host_els {int dummy; } ;
struct fc_bsg_host_del_rport {int dummy; } ;
struct fc_bsg_host_ct {int dummy; } ;
struct fc_bsg_host_add_rport {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  payload_len; } ;
struct TYPE_7__ {int /*<<< orphan*/  payload_len; } ;
struct bsg_job {int request_len; int reply_len; TYPE_2__ reply_payload; TYPE_1__ request_payload; struct fc_bsg_reply* reply; struct fc_bsg_request* request; } ;
struct Scsi_Host {TYPE_5__* hostt; int /*<<< orphan*/  transportt; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* bsg_request ) (struct bsg_job*) ;} ;
struct TYPE_11__ {long vendor_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBADR ; 
 int EINVAL ; 
 int ENOMSG ; 
 int ESRCH ; 
#define  FC_BSG_HST_ADD_RPORT 132 
#define  FC_BSG_HST_CT 131 
#define  FC_BSG_HST_DEL_RPORT 130 
#define  FC_BSG_HST_ELS_NOLOGIN 129 
#define  FC_BSG_HST_VENDOR 128 
 int /*<<< orphan*/  bsg_job_done (struct bsg_job*,int,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct bsg_job*) ; 
 struct fc_internal* to_fc_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fc_bsg_host_dispatch(struct Scsi_Host *shost, struct bsg_job *job)
{
	struct fc_internal *i = to_fc_internal(shost->transportt);
	struct fc_bsg_request *bsg_request = job->request;
	struct fc_bsg_reply *bsg_reply = job->reply;
	int cmdlen = sizeof(uint32_t);	/* start with length of msgcode */
	int ret;

	/* check if we really have all the request data needed */
	if (job->request_len < cmdlen) {
		ret = -ENOMSG;
		goto fail_host_msg;
	}

	/* Validate the host command */
	switch (bsg_request->msgcode) {
	case FC_BSG_HST_ADD_RPORT:
		cmdlen += sizeof(struct fc_bsg_host_add_rport);
		break;

	case FC_BSG_HST_DEL_RPORT:
		cmdlen += sizeof(struct fc_bsg_host_del_rport);
		break;

	case FC_BSG_HST_ELS_NOLOGIN:
		cmdlen += sizeof(struct fc_bsg_host_els);
		/* there better be a xmt and rcv payloads */
		if ((!job->request_payload.payload_len) ||
		    (!job->reply_payload.payload_len)) {
			ret = -EINVAL;
			goto fail_host_msg;
		}
		break;

	case FC_BSG_HST_CT:
		cmdlen += sizeof(struct fc_bsg_host_ct);
		/* there better be xmt and rcv payloads */
		if ((!job->request_payload.payload_len) ||
		    (!job->reply_payload.payload_len)) {
			ret = -EINVAL;
			goto fail_host_msg;
		}
		break;

	case FC_BSG_HST_VENDOR:
		cmdlen += sizeof(struct fc_bsg_host_vendor);
		if ((shost->hostt->vendor_id == 0L) ||
		    (bsg_request->rqst_data.h_vendor.vendor_id !=
			shost->hostt->vendor_id)) {
			ret = -ESRCH;
			goto fail_host_msg;
		}
		break;

	default:
		ret = -EBADR;
		goto fail_host_msg;
	}

	ret = i->f->bsg_request(job);
	if (!ret)
		return 0;

fail_host_msg:
	/* return the errno failure code as the only status */
	BUG_ON(job->reply_len < sizeof(uint32_t));
	bsg_reply->reply_payload_rcv_len = 0;
	bsg_reply->result = ret;
	job->reply_len = sizeof(uint32_t);
	bsg_job_done(job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);
	return 0;
}