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
typedef  int /*<<< orphan*/  uint32_t ;
struct qedf_rport {int /*<<< orphan*/  sid; struct qedf_ctx* qedf; int /*<<< orphan*/  flags; } ;
struct qedf_ioreq {int /*<<< orphan*/  refcount; int /*<<< orphan*/  xid; TYPE_3__* task; struct qedf_rport* fcport; } ;
struct qedf_els_cb_arg {struct qedf_ioreq* aborted_io_req; } ;
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; struct fc_lport* lport; } ;
struct fc_lport {int /*<<< orphan*/  r_a_tov; } ;
struct fc_els_rrq {void* rrq_rx_id; void* rrq_ox_id; int /*<<< orphan*/  rrq_s_id; int /*<<< orphan*/  rrq_cmd; } ;
typedef  int /*<<< orphan*/  rrq ;
struct TYPE_4__ {int /*<<< orphan*/  rx_id; } ;
struct TYPE_5__ {TYPE_1__ read_write; } ;
struct TYPE_6__ {TYPE_2__ tstorm_st_context; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ELS_RRQ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct qedf_ioreq*,struct qedf_ioreq*,...) ; 
 int /*<<< orphan*/  QEDF_LOG_ELS ; 
 int /*<<< orphan*/  QEDF_RPORT_SESSION_READY ; 
 int /*<<< orphan*/  hton24 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qedf_els_cb_arg*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int kref_read (int /*<<< orphan*/ *) ; 
 struct qedf_els_cb_arg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fc_els_rrq*,int /*<<< orphan*/ ,int) ; 
 int qedf_initiate_els (struct qedf_rport*,int /*<<< orphan*/ ,struct fc_els_rrq*,int,int /*<<< orphan*/ ,struct qedf_els_cb_arg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedf_release_cmd ; 
 int /*<<< orphan*/  qedf_rrq_compl ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qedf_send_rrq(struct qedf_ioreq *aborted_io_req)
{

	struct fc_els_rrq rrq;
	struct qedf_rport *fcport;
	struct fc_lport *lport;
	struct qedf_els_cb_arg *cb_arg = NULL;
	struct qedf_ctx *qedf;
	uint32_t sid;
	uint32_t r_a_tov;
	int rc;
	int refcount;

	if (!aborted_io_req) {
		QEDF_ERR(NULL, "abort_io_req is NULL.\n");
		return -EINVAL;
	}

	fcport = aborted_io_req->fcport;

	if (!fcport) {
		refcount = kref_read(&aborted_io_req->refcount);
		QEDF_ERR(NULL,
			 "RRQ work was queued prior to a flush xid=0x%x, refcount=%d.\n",
			 aborted_io_req->xid, refcount);
		kref_put(&aborted_io_req->refcount, qedf_release_cmd);
		return -EINVAL;
	}

	/* Check that fcport is still offloaded */
	if (!test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags)) {
		QEDF_ERR(NULL, "fcport is no longer offloaded.\n");
		return -EINVAL;
	}

	if (!fcport->qedf) {
		QEDF_ERR(NULL, "fcport->qedf is NULL.\n");
		return -EINVAL;
	}

	qedf = fcport->qedf;

	/*
	 * Sanity check that we can send a RRQ to make sure that refcount isn't
	 * 0
	 */
	refcount = kref_read(&aborted_io_req->refcount);
	if (refcount != 1) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_ELS,
			  "refcount for xid=%x io_req=%p refcount=%d is not 1.\n",
			  aborted_io_req->xid, aborted_io_req, refcount);
		return -EINVAL;
	}

	lport = qedf->lport;
	sid = fcport->sid;
	r_a_tov = lport->r_a_tov;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS, "Sending RRQ orig "
		   "io = %p, orig_xid = 0x%x\n", aborted_io_req,
		   aborted_io_req->xid);
	memset(&rrq, 0, sizeof(rrq));

	cb_arg = kzalloc(sizeof(struct qedf_els_cb_arg), GFP_NOIO);
	if (!cb_arg) {
		QEDF_ERR(&(qedf->dbg_ctx), "Unable to allocate cb_arg for "
			  "RRQ\n");
		rc = -ENOMEM;
		goto rrq_err;
	}

	cb_arg->aborted_io_req = aborted_io_req;

	rrq.rrq_cmd = ELS_RRQ;
	hton24(rrq.rrq_s_id, sid);
	rrq.rrq_ox_id = htons(aborted_io_req->xid);
	rrq.rrq_rx_id =
	    htons(aborted_io_req->task->tstorm_st_context.read_write.rx_id);

	rc = qedf_initiate_els(fcport, ELS_RRQ, &rrq, sizeof(rrq),
	    qedf_rrq_compl, cb_arg, r_a_tov);

rrq_err:
	if (rc) {
		QEDF_ERR(&(qedf->dbg_ctx), "RRQ failed - release orig io "
			  "req 0x%x\n", aborted_io_req->xid);
		kfree(cb_arg);
		kref_put(&aborted_io_req->refcount, qedf_release_cmd);
	}
	return rc;
}