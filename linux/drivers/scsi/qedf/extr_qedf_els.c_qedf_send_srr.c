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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct qedf_rport {struct qedf_ctx* qedf; int /*<<< orphan*/  flags; } ;
struct qedf_ioreq {int /*<<< orphan*/  flags; int /*<<< orphan*/  refcount; int /*<<< orphan*/  xid; int /*<<< orphan*/  rx_id; struct qedf_rport* fcport; } ;
struct qedf_els_cb_arg {struct qedf_ioreq* aborted_io_req; } ;
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; struct fc_lport* lport; } ;
struct fcp_srr {int /*<<< orphan*/  srr_r_ctl; int /*<<< orphan*/  srr_rel_off; void* srr_rx_id; void* srr_ox_id; int /*<<< orphan*/  srr_op; } ;
struct fc_lport {int /*<<< orphan*/  r_a_tov; } ;
typedef  int /*<<< orphan*/  srr ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ELS_SRR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  QEDF_CMD_SRR_SENT ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct qedf_ioreq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDF_LOG_ELS ; 
 int /*<<< orphan*/  QEDF_RPORT_SESSION_READY ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qedf_els_cb_arg*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct qedf_els_cb_arg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fcp_srr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qedf_initiate_abts (struct qedf_ioreq*,int) ; 
 int qedf_initiate_els (struct qedf_rport*,int /*<<< orphan*/ ,struct fcp_srr*,int,int /*<<< orphan*/ ,struct qedf_els_cb_arg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedf_release_cmd ; 
 int /*<<< orphan*/  qedf_srr_compl ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qedf_send_srr(struct qedf_ioreq *orig_io_req, u32 offset, u8 r_ctl)
{
	struct fcp_srr srr;
	struct qedf_ctx *qedf;
	struct qedf_rport *fcport;
	struct fc_lport *lport;
	struct qedf_els_cb_arg *cb_arg = NULL;
	u32 r_a_tov;
	int rc;

	if (!orig_io_req) {
		QEDF_ERR(NULL, "orig_io_req is NULL.\n");
		return -EINVAL;
	}

	fcport = orig_io_req->fcport;

	/* Check that fcport is still offloaded */
	if (!test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags)) {
		QEDF_ERR(NULL, "fcport is no longer offloaded.\n");
		return -EINVAL;
	}

	if (!fcport->qedf) {
		QEDF_ERR(NULL, "fcport->qedf is NULL.\n");
		return -EINVAL;
	}

	/* Take reference until SRR command completion */
	kref_get(&orig_io_req->refcount);

	qedf = fcport->qedf;
	lport = qedf->lport;
	r_a_tov = lport->r_a_tov;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS, "Sending SRR orig_io=%p, "
		   "orig_xid=0x%x\n", orig_io_req, orig_io_req->xid);
	memset(&srr, 0, sizeof(srr));

	cb_arg = kzalloc(sizeof(struct qedf_els_cb_arg), GFP_NOIO);
	if (!cb_arg) {
		QEDF_ERR(&(qedf->dbg_ctx), "Unable to allocate cb_arg for "
			  "SRR\n");
		rc = -ENOMEM;
		goto srr_err;
	}

	cb_arg->aborted_io_req = orig_io_req;

	srr.srr_op = ELS_SRR;
	srr.srr_ox_id = htons(orig_io_req->xid);
	srr.srr_rx_id = htons(orig_io_req->rx_id);
	srr.srr_rel_off = htonl(offset);
	srr.srr_r_ctl = r_ctl;

	rc = qedf_initiate_els(fcport, ELS_SRR, &srr, sizeof(srr),
	    qedf_srr_compl, cb_arg, r_a_tov);

srr_err:
	if (rc) {
		QEDF_ERR(&(qedf->dbg_ctx), "SRR failed - release orig_io_req"
			  "=0x%x\n", orig_io_req->xid);
		kfree(cb_arg);
		/* If we fail to queue SRR, send ABTS to orig_io */
		qedf_initiate_abts(orig_io_req, true);
		kref_put(&orig_io_req->refcount, qedf_release_cmd);
	} else
		/* Tell other threads that SRR is in progress */
		set_bit(QEDF_CMD_SRR_SENT, &orig_io_req->flags);

	return rc;
}