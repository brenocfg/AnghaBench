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
struct qedf_ioreq {scalar_t__ event; scalar_t__ xid; int /*<<< orphan*/  refcount; int /*<<< orphan*/  timeout_work; struct qedf_els_cb_arg* cb_arg; } ;
struct qedf_els_cb_arg {int /*<<< orphan*/  r_ctl; int /*<<< orphan*/  offset; } ;
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; } ;
struct fcoe_cqe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ QEDF_IOREQ_EV_ELS_TMO ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct qedf_els_cb_arg*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedf_release_cmd ; 
 int qedf_send_srr (struct qedf_ioreq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qedf_process_seq_cleanup_compl(struct qedf_ctx *qedf,
	struct fcoe_cqe *cqe, struct qedf_ioreq *io_req)
{
	int rc;
	struct qedf_els_cb_arg *cb_arg;

	cb_arg = io_req->cb_arg;

	/* If we timed out just free resources */
	if (io_req->event == QEDF_IOREQ_EV_ELS_TMO || !cqe) {
		QEDF_ERR(&qedf->dbg_ctx,
			 "cqe is NULL or timeout event (0x%x)", io_req->event);
		goto free;
	}

	/* Kill the timer we put on the request */
	cancel_delayed_work_sync(&io_req->timeout_work);

	rc = qedf_send_srr(io_req, cb_arg->offset, cb_arg->r_ctl);
	if (rc)
		QEDF_ERR(&(qedf->dbg_ctx), "Unable to send SRR, I/O will "
		    "abort, xid=0x%x.\n", io_req->xid);
free:
	kfree(cb_arg);
	kref_put(&io_req->refcount, qedf_release_cmd);
}