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
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_hba {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  a_Minor; int /*<<< orphan*/  a_Major; } ;
struct get_mgmt_rev_reply {TYPE_3__ info; } ;
struct get_mgmt_rev {int dummy; } ;
struct fc_bsg_request {int dummy; } ;
struct TYPE_4__ {scalar_t__ vendor_rsp; } ;
struct TYPE_5__ {TYPE_1__ vendor_reply; } ;
struct fc_bsg_reply {int result; int /*<<< orphan*/  reply_payload_rcv_len; TYPE_2__ reply_data; } ;
struct bsg_job {int request_len; int reply_len; struct fc_bsg_reply* reply; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_LIBDFC ; 
 int /*<<< orphan*/  MANAGEMENT_MAJOR_REV ; 
 int /*<<< orphan*/  MANAGEMENT_MINOR_REV ; 
 int /*<<< orphan*/  bsg_job_done (struct bsg_job*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_bsg_to_shost (struct bsg_job*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct lpfc_vport* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_bsg_get_dfc_rev(struct bsg_job *job)
{
	struct lpfc_vport *vport = shost_priv(fc_bsg_to_shost(job));
	struct fc_bsg_reply *bsg_reply = job->reply;
	struct lpfc_hba *phba = vport->phba;
	struct get_mgmt_rev_reply *event_reply;
	int rc = 0;

	if (job->request_len <
	    sizeof(struct fc_bsg_request) + sizeof(struct get_mgmt_rev)) {
		lpfc_printf_log(phba, KERN_WARNING, LOG_LIBDFC,
				"2740 Received GET_DFC_REV request below "
				"minimum size\n");
		rc = -EINVAL;
		goto job_error;
	}

	event_reply = (struct get_mgmt_rev_reply *)
		bsg_reply->reply_data.vendor_reply.vendor_rsp;

	if (job->reply_len <
	    sizeof(struct fc_bsg_request) + sizeof(struct get_mgmt_rev_reply)) {
		lpfc_printf_log(phba, KERN_WARNING, LOG_LIBDFC,
				"2741 Received GET_DFC_REV reply below "
				"minimum size\n");
		rc = -EINVAL;
		goto job_error;
	}

	event_reply->info.a_Major = MANAGEMENT_MAJOR_REV;
	event_reply->info.a_Minor = MANAGEMENT_MINOR_REV;
job_error:
	bsg_reply->result = rc;
	if (rc == 0)
		bsg_job_done(job, bsg_reply->result,
			       bsg_reply->reply_payload_rcv_len);
	return rc;
}