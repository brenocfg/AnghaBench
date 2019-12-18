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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  size_t u16 ;
struct qedf_rport {int /*<<< orphan*/  rport_lock; struct fcoe_wqe* sq; int /*<<< orphan*/  sid; TYPE_2__* rdata; int /*<<< orphan*/  flags; int /*<<< orphan*/  rport; struct qedf_ctx* qedf; } ;
struct fc_frame_header {int dummy; } ;
struct qedf_mp_req {struct fc_frame_header req_fc_hdr; int /*<<< orphan*/  req_buf; } ;
struct qedf_ioreq {void (* cb_func ) (struct qedf_els_cb_arg*) ;int /*<<< orphan*/  flags; int /*<<< orphan*/  xid; int /*<<< orphan*/  refcount; struct qedf_els_cb_arg* cb_arg; int /*<<< orphan*/  mp_req; int /*<<< orphan*/  cpu; int /*<<< orphan*/  data_xfer_len; struct qedf_rport* fcport; int /*<<< orphan*/  cmd_type; int /*<<< orphan*/ * sc_cmd; } ;
struct qedf_els_cb_arg {unsigned int op; struct qedf_ioreq* io_req; } ;
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/  tasks; struct fc_lport* lport; } ;
struct fcoe_wqe {int dummy; } ;
struct fc_lport {scalar_t__ state; int /*<<< orphan*/  link_up; } ;
struct e4_fcoe_task_context {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  port_id; } ;
struct TYPE_4__ {TYPE_1__ ids; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 unsigned int ELS_AUTH_ELS ; 
 unsigned int ELS_LS_RJT ; 
 int ENOMEM ; 
 int FC_FC_END_SEQ ; 
 int FC_FC_FIRST_SEQ ; 
 int FC_FC_SEQ_INIT ; 
 int /*<<< orphan*/  FC_RCTL_ELS_REQ ; 
 int /*<<< orphan*/  FC_TYPE_ELS ; 
 scalar_t__ LPORT_ST_READY ; 
 int /*<<< orphan*/  QEDF_CMD_OUTSTANDING ; 
 int /*<<< orphan*/  QEDF_ELS ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  QEDF_LOG_ELS ; 
 int /*<<< orphan*/  QEDF_RPORT_SESSION_READY ; 
 int /*<<< orphan*/  __fc_fill_fc_hdr (struct fc_frame_header*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int fc_remote_port_chkready (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fcoe_wqe*,int /*<<< orphan*/ ,int) ; 
 struct qedf_ioreq* qedf_alloc_cmd (struct qedf_rport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedf_cmd_timer_set (struct qedf_ctx*,struct qedf_ioreq*,int /*<<< orphan*/ ) ; 
 size_t qedf_get_sqe_idx (struct qedf_rport*) ; 
 struct e4_fcoe_task_context* qedf_get_task_mem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int qedf_init_mp_req (struct qedf_ioreq*) ; 
 int /*<<< orphan*/  qedf_init_mp_task (struct qedf_ioreq*,struct e4_fcoe_task_context*,struct fcoe_wqe*) ; 
 int /*<<< orphan*/  qedf_release_cmd ; 
 int /*<<< orphan*/  qedf_ring_doorbell (struct qedf_rport*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qedf_initiate_els(struct qedf_rport *fcport, unsigned int op,
	void *data, uint32_t data_len,
	void (*cb_func)(struct qedf_els_cb_arg *cb_arg),
	struct qedf_els_cb_arg *cb_arg, uint32_t timer_msec)
{
	struct qedf_ctx *qedf;
	struct fc_lport *lport;
	struct qedf_ioreq *els_req;
	struct qedf_mp_req *mp_req;
	struct fc_frame_header *fc_hdr;
	struct e4_fcoe_task_context *task;
	int rc = 0;
	uint32_t did, sid;
	uint16_t xid;
	struct fcoe_wqe *sqe;
	unsigned long flags;
	u16 sqe_idx;

	if (!fcport) {
		QEDF_ERR(NULL, "fcport is NULL");
		rc = -EINVAL;
		goto els_err;
	}

	qedf = fcport->qedf;
	lport = qedf->lport;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS, "Sending ELS\n");

	rc = fc_remote_port_chkready(fcport->rport);
	if (rc) {
		QEDF_ERR(&(qedf->dbg_ctx), "els 0x%x: rport not ready\n", op);
		rc = -EAGAIN;
		goto els_err;
	}
	if (lport->state != LPORT_ST_READY || !(lport->link_up)) {
		QEDF_ERR(&(qedf->dbg_ctx), "els 0x%x: link is not ready\n",
			  op);
		rc = -EAGAIN;
		goto els_err;
	}

	if (!test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags)) {
		QEDF_ERR(&(qedf->dbg_ctx), "els 0x%x: fcport not ready\n", op);
		rc = -EINVAL;
		goto els_err;
	}

	els_req = qedf_alloc_cmd(fcport, QEDF_ELS);
	if (!els_req) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_ELS,
			  "Failed to alloc ELS request 0x%x\n", op);
		rc = -ENOMEM;
		goto els_err;
	}

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS, "initiate_els els_req = "
		   "0x%p cb_arg = %p xid = %x\n", els_req, cb_arg,
		   els_req->xid);
	els_req->sc_cmd = NULL;
	els_req->cmd_type = QEDF_ELS;
	els_req->fcport = fcport;
	els_req->cb_func = cb_func;
	cb_arg->io_req = els_req;
	cb_arg->op = op;
	els_req->cb_arg = cb_arg;
	els_req->data_xfer_len = data_len;

	/* Record which cpu this request is associated with */
	els_req->cpu = smp_processor_id();

	mp_req = (struct qedf_mp_req *)&(els_req->mp_req);
	rc = qedf_init_mp_req(els_req);
	if (rc) {
		QEDF_ERR(&(qedf->dbg_ctx), "ELS MP request init failed\n");
		kref_put(&els_req->refcount, qedf_release_cmd);
		goto els_err;
	} else {
		rc = 0;
	}

	/* Fill ELS Payload */
	if ((op >= ELS_LS_RJT) && (op <= ELS_AUTH_ELS)) {
		memcpy(mp_req->req_buf, data, data_len);
	} else {
		QEDF_ERR(&(qedf->dbg_ctx), "Invalid ELS op 0x%x\n", op);
		els_req->cb_func = NULL;
		els_req->cb_arg = NULL;
		kref_put(&els_req->refcount, qedf_release_cmd);
		rc = -EINVAL;
	}

	if (rc)
		goto els_err;

	/* Fill FC header */
	fc_hdr = &(mp_req->req_fc_hdr);

	did = fcport->rdata->ids.port_id;
	sid = fcport->sid;

	__fc_fill_fc_hdr(fc_hdr, FC_RCTL_ELS_REQ, did, sid,
			   FC_TYPE_ELS, FC_FC_FIRST_SEQ | FC_FC_END_SEQ |
			   FC_FC_SEQ_INIT, 0);

	/* Obtain exchange id */
	xid = els_req->xid;

	spin_lock_irqsave(&fcport->rport_lock, flags);

	sqe_idx = qedf_get_sqe_idx(fcport);
	sqe = &fcport->sq[sqe_idx];
	memset(sqe, 0, sizeof(struct fcoe_wqe));

	/* Initialize task context for this IO request */
	task = qedf_get_task_mem(&qedf->tasks, xid);
	qedf_init_mp_task(els_req, task, sqe);

	/* Put timer on original I/O request */
	if (timer_msec)
		qedf_cmd_timer_set(qedf, els_req, timer_msec);

	/* Ring doorbell */
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS, "Ringing doorbell for ELS "
		   "req\n");
	qedf_ring_doorbell(fcport);
	set_bit(QEDF_CMD_OUTSTANDING, &els_req->flags);

	spin_unlock_irqrestore(&fcport->rport_lock, flags);
els_err:
	return rc;
}