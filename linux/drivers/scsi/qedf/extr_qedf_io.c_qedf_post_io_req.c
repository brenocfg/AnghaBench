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
typedef  size_t u16 ;
struct TYPE_3__ {char* ptr; } ;
struct scsi_cmnd {scalar_t__ sc_data_direction; TYPE_2__* device; TYPE_1__ SCp; } ;
struct qedf_rport {struct fcoe_wqe* sq; int /*<<< orphan*/  flags; } ;
struct qedf_ioreq {size_t xid; int lun; struct scsi_cmnd* sc_cmd; int /*<<< orphan*/  flags; int /*<<< orphan*/  refcount; scalar_t__ io_req_flags; int /*<<< orphan*/  cpu; int /*<<< orphan*/  sge_type; int /*<<< orphan*/  data_xfer_len; } ;
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/  tasks; int /*<<< orphan*/  control_requests; int /*<<< orphan*/  output_requests; int /*<<< orphan*/  input_requests; } ;
struct fcoe_wqe {int dummy; } ;
struct fc_lport {int dummy; } ;
struct e4_fcoe_task_context {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  enum fcoe_task_type { ____Placeholder_fcoe_task_type } fcoe_task_type ;
struct TYPE_4__ {scalar_t__ lun; struct Scsi_Host* host; } ;

/* Variables and functions */
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int FCOE_TASK_TYPE_READ_INITIATOR ; 
 int FCOE_TASK_TYPE_WRITE_INITIATOR ; 
 int /*<<< orphan*/  QEDF_CMD_OUTSTANDING ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QEDF_IOREQ_FAST_SGE ; 
 int /*<<< orphan*/  QEDF_IO_TRACE_REQ ; 
 scalar_t__ QEDF_READ ; 
 int /*<<< orphan*/  QEDF_RPORT_SESSION_READY ; 
 int /*<<< orphan*/  QEDF_RPORT_UPLOADING_CONNECTION ; 
 int /*<<< orphan*/  QEDF_WARN (int /*<<< orphan*/ *,char*,size_t) ; 
 scalar_t__ QEDF_WRITE ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct qedf_ctx* lport_priv (struct fc_lport*) ; 
 int /*<<< orphan*/  memset (struct fcoe_wqe*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qedf_build_bd_list_from_sg (struct qedf_ioreq*) ; 
 size_t qedf_get_sqe_idx (struct qedf_rport*) ; 
 struct e4_fcoe_task_context* qedf_get_task_mem (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  qedf_init_task (struct qedf_rport*,struct fc_lport*,struct qedf_ioreq*,struct e4_fcoe_task_context*,struct fcoe_wqe*) ; 
 scalar_t__ qedf_io_tracing ; 
 int /*<<< orphan*/  qedf_release_cmd ; 
 int /*<<< orphan*/  qedf_ring_doorbell (struct qedf_rport*) ; 
 int /*<<< orphan*/  qedf_trace_io (struct qedf_rport*,struct qedf_ioreq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct fc_lport* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qedf_post_io_req(struct qedf_rport *fcport, struct qedf_ioreq *io_req)
{
	struct scsi_cmnd *sc_cmd = io_req->sc_cmd;
	struct Scsi_Host *host = sc_cmd->device->host;
	struct fc_lport *lport = shost_priv(host);
	struct qedf_ctx *qedf = lport_priv(lport);
	struct e4_fcoe_task_context *task_ctx;
	u16 xid;
	enum fcoe_task_type req_type = 0;
	struct fcoe_wqe *sqe;
	u16 sqe_idx;

	/* Initialize rest of io_req fileds */
	io_req->data_xfer_len = scsi_bufflen(sc_cmd);
	sc_cmd->SCp.ptr = (char *)io_req;
	io_req->sge_type = QEDF_IOREQ_FAST_SGE; /* Assume fast SGL by default */

	/* Record which cpu this request is associated with */
	io_req->cpu = smp_processor_id();

	if (sc_cmd->sc_data_direction == DMA_FROM_DEVICE) {
		req_type = FCOE_TASK_TYPE_READ_INITIATOR;
		io_req->io_req_flags = QEDF_READ;
		qedf->input_requests++;
	} else if (sc_cmd->sc_data_direction == DMA_TO_DEVICE) {
		req_type = FCOE_TASK_TYPE_WRITE_INITIATOR;
		io_req->io_req_flags = QEDF_WRITE;
		qedf->output_requests++;
	} else {
		io_req->io_req_flags = 0;
		qedf->control_requests++;
	}

	xid = io_req->xid;

	/* Build buffer descriptor list for firmware from sg list */
	if (qedf_build_bd_list_from_sg(io_req)) {
		QEDF_ERR(&(qedf->dbg_ctx), "BD list creation failed.\n");
		/* Release cmd will release io_req, but sc_cmd is assigned */
		io_req->sc_cmd = NULL;
		kref_put(&io_req->refcount, qedf_release_cmd);
		return -EAGAIN;
	}

	if (!test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags) ||
	    test_bit(QEDF_RPORT_UPLOADING_CONNECTION, &fcport->flags)) {
		QEDF_ERR(&(qedf->dbg_ctx), "Session not offloaded yet.\n");
		/* Release cmd will release io_req, but sc_cmd is assigned */
		io_req->sc_cmd = NULL;
		kref_put(&io_req->refcount, qedf_release_cmd);
		return -EINVAL;
	}

	/* Record LUN number for later use if we neeed them */
	io_req->lun = (int)sc_cmd->device->lun;

	/* Obtain free SQE */
	sqe_idx = qedf_get_sqe_idx(fcport);
	sqe = &fcport->sq[sqe_idx];
	memset(sqe, 0, sizeof(struct fcoe_wqe));

	/* Get the task context */
	task_ctx = qedf_get_task_mem(&qedf->tasks, xid);
	if (!task_ctx) {
		QEDF_WARN(&(qedf->dbg_ctx), "task_ctx is NULL, xid=%d.\n",
			   xid);
		/* Release cmd will release io_req, but sc_cmd is assigned */
		io_req->sc_cmd = NULL;
		kref_put(&io_req->refcount, qedf_release_cmd);
		return -EINVAL;
	}

	qedf_init_task(fcport, lport, io_req, task_ctx, sqe);

	/* Ring doorbell */
	qedf_ring_doorbell(fcport);

	/* Set that command is with the firmware now */
	set_bit(QEDF_CMD_OUTSTANDING, &io_req->flags);

	if (qedf_io_tracing && io_req->sc_cmd)
		qedf_trace_io(fcport, io_req, QEDF_IO_TRACE_REQ);

	return false;
}