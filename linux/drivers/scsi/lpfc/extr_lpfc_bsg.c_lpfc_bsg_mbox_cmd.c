#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_hba {int dummy; } ;
struct TYPE_3__ {scalar_t__ vendor_cmd; } ;
struct TYPE_4__ {TYPE_1__ h_vendor; } ;
struct fc_bsg_request {TYPE_2__ rqst_data; } ;
struct fc_bsg_reply {int result; scalar_t__ reply_payload_rcv_len; } ;
struct dfc_mbox_req {scalar_t__ extSeqNum; scalar_t__ extMboxTag; } ;
struct bsg_job {int request_len; int /*<<< orphan*/ * dd_data; struct fc_bsg_reply* reply; struct fc_bsg_request* request; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_LIBDFC ; 
 int /*<<< orphan*/  bsg_job_done (struct bsg_job*,int,scalar_t__) ; 
 int /*<<< orphan*/  fc_bsg_to_shost (struct bsg_job*) ; 
 int lpfc_bsg_issue_mbox (struct lpfc_hba*,struct bsg_job*,struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 struct lpfc_vport* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_bsg_mbox_cmd(struct bsg_job *job)
{
	struct lpfc_vport *vport = shost_priv(fc_bsg_to_shost(job));
	struct fc_bsg_request *bsg_request = job->request;
	struct fc_bsg_reply *bsg_reply = job->reply;
	struct lpfc_hba *phba = vport->phba;
	struct dfc_mbox_req *mbox_req;
	int rc = 0;

	/* mix-and-match backward compatibility */
	bsg_reply->reply_payload_rcv_len = 0;
	if (job->request_len <
	    sizeof(struct fc_bsg_request) + sizeof(struct dfc_mbox_req)) {
		lpfc_printf_log(phba, KERN_INFO, LOG_LIBDFC,
				"2737 Mix-and-match backward compatibility "
				"between MBOX_REQ old size:%d and "
				"new request size:%d\n",
				(int)(job->request_len -
				      sizeof(struct fc_bsg_request)),
				(int)sizeof(struct dfc_mbox_req));
		mbox_req = (struct dfc_mbox_req *)
				bsg_request->rqst_data.h_vendor.vendor_cmd;
		mbox_req->extMboxTag = 0;
		mbox_req->extSeqNum = 0;
	}

	rc = lpfc_bsg_issue_mbox(phba, job, vport);

	if (rc == 0) {
		/* job done */
		bsg_reply->result = 0;
		job->dd_data = NULL;
		bsg_job_done(job, bsg_reply->result,
			       bsg_reply->reply_payload_rcv_len);
	} else if (rc == 1)
		/* job submitted, will complete later*/
		rc = 0; /* return zero, no error */
	else {
		/* some error occurred */
		bsg_reply->result = rc;
		job->dd_data = NULL;
	}

	return rc;
}