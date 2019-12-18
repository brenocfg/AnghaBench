#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct qla_dport_diag {int /*<<< orphan*/  options; int /*<<< orphan*/  buf; } ;
struct TYPE_11__ {int /*<<< orphan*/ * vendor_rsp; } ;
struct TYPE_12__ {TYPE_3__ vendor_reply; } ;
struct fc_bsg_reply {int reply_payload_rcv_len; int result; TYPE_4__ reply_data; } ;
struct TYPE_10__ {int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg_list; } ;
struct TYPE_9__ {int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg_list; } ;
struct bsg_job {int reply_len; TYPE_2__ reply_payload; TYPE_1__ request_payload; struct fc_bsg_reply* reply; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  hw; } ;
typedef  TYPE_5__ scsi_qla_host_t ;

/* Variables and functions */
 int DID_OK ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  EXT_STATUS_MAILBOX ; 
 int /*<<< orphan*/  EXT_STATUS_OK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_QLA27XX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_QLA28XX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_QLA83XX (int /*<<< orphan*/ ) ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  bsg_job_done (struct bsg_job*,int,int) ; 
 struct Scsi_Host* fc_bsg_to_shost (struct bsg_job*) ; 
 int /*<<< orphan*/  kfree (struct qla_dport_diag*) ; 
 struct qla_dport_diag* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_5__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int qla26xx_dport_diagnostics (TYPE_5__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_copy_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qla_dport_diag*,int) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qla_dport_diag*,int) ; 
 TYPE_5__* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int
qla2x00_do_dport_diagnostics(struct bsg_job *bsg_job)
{
	struct fc_bsg_reply *bsg_reply = bsg_job->reply;
	struct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	int rval;
	struct qla_dport_diag *dd;

	if (!IS_QLA83XX(vha->hw) && !IS_QLA27XX(vha->hw) &&
	    !IS_QLA28XX(vha->hw))
		return -EPERM;

	dd = kmalloc(sizeof(*dd), GFP_KERNEL);
	if (!dd) {
		ql_log(ql_log_warn, vha, 0x70db,
		    "Failed to allocate memory for dport.\n");
		return -ENOMEM;
	}

	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
	    bsg_job->request_payload.sg_cnt, dd, sizeof(*dd));

	rval = qla26xx_dport_diagnostics(
	    vha, dd->buf, sizeof(dd->buf), dd->options);
	if (rval == QLA_SUCCESS) {
		sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
		    bsg_job->reply_payload.sg_cnt, dd, sizeof(*dd));
	}

	bsg_reply->reply_payload_rcv_len = sizeof(*dd);
	bsg_reply->reply_data.vendor_reply.vendor_rsp[0] =
	    rval ? EXT_STATUS_MAILBOX : EXT_STATUS_OK;

	bsg_job->reply_len = sizeof(*bsg_reply);
	bsg_reply->result = DID_OK << 16;
	bsg_job_done(bsg_job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);

	kfree(dd);

	return 0;
}