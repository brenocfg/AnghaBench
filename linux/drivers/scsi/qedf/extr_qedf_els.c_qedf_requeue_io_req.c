#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qedf_rport {int /*<<< orphan*/  rport_lock; TYPE_1__* qedf; int /*<<< orphan*/  free_sqes; } ;
struct qedf_ioreq {int /*<<< orphan*/  xid; int /*<<< orphan*/  refcount; int /*<<< orphan*/ * sc_cmd; struct qedf_rport* fcport; } ;
struct TYPE_2__ {int /*<<< orphan*/  dbg_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDF_LOG_ELS ; 
 int /*<<< orphan*/  QEDF_SCSI_CMD ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct qedf_ioreq* qedf_alloc_cmd (struct qedf_rport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedf_initiate_abts (struct qedf_ioreq*,int) ; 
 scalar_t__ qedf_post_io_req (struct qedf_rport*,struct qedf_ioreq*) ; 
 int /*<<< orphan*/  qedf_release_cmd ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool qedf_requeue_io_req(struct qedf_ioreq *orig_io_req)
{
	struct qedf_rport *fcport;
	struct qedf_ioreq *new_io_req;
	unsigned long flags;
	bool rc = false;

	fcport = orig_io_req->fcport;
	if (!fcport) {
		QEDF_ERR(NULL, "fcport is NULL.\n");
		goto out;
	}

	if (!orig_io_req->sc_cmd) {
		QEDF_ERR(&(fcport->qedf->dbg_ctx), "sc_cmd is NULL for "
		    "xid=0x%x.\n", orig_io_req->xid);
		goto out;
	}

	new_io_req = qedf_alloc_cmd(fcport, QEDF_SCSI_CMD);
	if (!new_io_req) {
		QEDF_ERR(&(fcport->qedf->dbg_ctx), "Could not allocate new "
		    "io_req.\n");
		goto out;
	}

	new_io_req->sc_cmd = orig_io_req->sc_cmd;

	/*
	 * This keeps the sc_cmd struct from being returned to the tape
	 * driver and being requeued twice. We do need to put a reference
	 * for the original I/O request since we will not do a SCSI completion
	 * for it.
	 */
	orig_io_req->sc_cmd = NULL;
	kref_put(&orig_io_req->refcount, qedf_release_cmd);

	spin_lock_irqsave(&fcport->rport_lock, flags);

	/* kref for new command released in qedf_post_io_req on error */
	if (qedf_post_io_req(fcport, new_io_req)) {
		QEDF_ERR(&(fcport->qedf->dbg_ctx), "Unable to post io_req\n");
		/* Return SQE to pool */
		atomic_inc(&fcport->free_sqes);
	} else {
		QEDF_INFO(&(fcport->qedf->dbg_ctx), QEDF_LOG_ELS,
		    "Reissued SCSI command from  orig_xid=0x%x on "
		    "new_xid=0x%x.\n", orig_io_req->xid, new_io_req->xid);
		/*
		 * Abort the original I/O but do not return SCSI command as
		 * it has been reissued on another OX_ID.
		 */
		spin_unlock_irqrestore(&fcport->rport_lock, flags);
		qedf_initiate_abts(orig_io_req, false);
		goto out;
	}

	spin_unlock_irqrestore(&fcport->rport_lock, flags);
out:
	return rc;
}