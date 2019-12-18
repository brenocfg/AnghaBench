#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u64 ;
typedef  int u16 ;
struct TYPE_10__ {int /*<<< orphan*/ * ptr; } ;
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;TYPE_3__ SCp; int /*<<< orphan*/ * cmnd; TYPE_5__* device; TYPE_4__* request; } ;
struct qedf_rport {int retry_delay_timestamp; scalar_t__ lun_reset_lun; int /*<<< orphan*/  flags; } ;
struct qedf_ioreq {int xid; int fcp_rsp_len; int cdb_status; int fcp_status; int /*<<< orphan*/  refcount; struct scsi_cmnd* sc_cmd; int /*<<< orphan*/  flags; scalar_t__ fcp_resid; scalar_t__ fcp_rsp_code; struct qedf_rport* fcport; } ;
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/  busy; int /*<<< orphan*/  task_set_fulls; TYPE_2__* lport; int /*<<< orphan*/  tasks; } ;
struct TYPE_13__ {int /*<<< orphan*/  flags; } ;
struct fcoe_cqe_rsp_info {int retry_delay_timer; int /*<<< orphan*/  fw_residual; TYPE_6__ rsp_flags; int /*<<< orphan*/  fw_error_flags; } ;
struct TYPE_14__ {struct fcoe_cqe_rsp_info rsp_info; } ;
struct fcoe_cqe {TYPE_7__ cqe_info; } ;
struct e4_fcoe_task_context {int dummy; } ;
struct TYPE_12__ {scalar_t__ lun; int /*<<< orphan*/  id; } ;
struct TYPE_11__ {int /*<<< orphan*/  q; } ;
struct TYPE_9__ {TYPE_1__* host; } ;
struct TYPE_8__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int DID_BUS_BUSY ; 
 int DID_ERROR ; 
 int DID_OK ; 
 int /*<<< orphan*/  FCOE_CQE_RSP_INFO_FW_UNDERRUN ; 
#define  FC_GOOD 128 
 scalar_t__ GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HZ ; 
 int /*<<< orphan*/  QEDF_CMD_IN_ABORT ; 
 int /*<<< orphan*/  QEDF_CMD_IN_CLEANUP ; 
 int /*<<< orphan*/  QEDF_CMD_OUTSTANDING ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  QEDF_IO_TRACE_RSP ; 
 int /*<<< orphan*/  QEDF_LOG_IO ; 
 int QEDF_RETRY_DELAY_MAX ; 
 int /*<<< orphan*/  QEDF_RPORT_IN_LUN_RESET ; 
 int /*<<< orphan*/  QEDF_RPORT_IN_TARGET_RESET ; 
 int /*<<< orphan*/  QEDF_WARN (int /*<<< orphan*/ *,char*,...) ; 
 int SAM_STAT_BUSY ; 
 int SAM_STAT_TASK_SET_FULL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int jiffies ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int kref_read (int /*<<< orphan*/ *) ; 
 struct e4_fcoe_task_context* qedf_get_task_mem (int /*<<< orphan*/ *,int) ; 
 scalar_t__ qedf_io_tracing ; 
 int /*<<< orphan*/  qedf_parse_fcp_rsp (struct qedf_ioreq*,struct fcoe_cqe_rsp_info*) ; 
 int /*<<< orphan*/  qedf_release_cmd ; 
 int /*<<< orphan*/  qedf_retry_delay ; 
 int /*<<< orphan*/  qedf_trace_io (struct qedf_rport*,struct qedf_ioreq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedf_unmap_sg_list (struct qedf_ctx*,struct qedf_ioreq*) ; 
 scalar_t__ scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qedf_scsi_completion(struct qedf_ctx *qedf, struct fcoe_cqe *cqe,
	struct qedf_ioreq *io_req)
{
	u16 xid;
	struct e4_fcoe_task_context *task_ctx;
	struct scsi_cmnd *sc_cmd;
	struct fcoe_cqe_rsp_info *fcp_rsp;
	struct qedf_rport *fcport;
	int refcount;
	u16 scope, qualifier = 0;
	u8 fw_residual_flag = 0;

	if (!io_req)
		return;
	if (!cqe)
		return;

	if (!test_bit(QEDF_CMD_OUTSTANDING, &io_req->flags) ||
	    test_bit(QEDF_CMD_IN_CLEANUP, &io_req->flags) ||
	    test_bit(QEDF_CMD_IN_ABORT, &io_req->flags)) {
		QEDF_ERR(&qedf->dbg_ctx,
			 "io_req xid=0x%x already in cleanup or abort processing or already completed.\n",
			 io_req->xid);
		return;
	}

	xid = io_req->xid;
	task_ctx = qedf_get_task_mem(&qedf->tasks, xid);
	sc_cmd = io_req->sc_cmd;
	fcp_rsp = &cqe->cqe_info.rsp_info;

	if (!sc_cmd) {
		QEDF_WARN(&(qedf->dbg_ctx), "sc_cmd is NULL!\n");
		return;
	}

	if (!sc_cmd->SCp.ptr) {
		QEDF_WARN(&(qedf->dbg_ctx), "SCp.ptr is NULL, returned in "
		    "another context.\n");
		return;
	}

	if (!sc_cmd->device) {
		QEDF_ERR(&qedf->dbg_ctx,
			 "Device for sc_cmd %p is NULL.\n", sc_cmd);
		return;
	}

	if (!sc_cmd->request) {
		QEDF_WARN(&(qedf->dbg_ctx), "sc_cmd->request is NULL, "
		    "sc_cmd=%p.\n", sc_cmd);
		return;
	}

	if (!sc_cmd->request->q) {
		QEDF_WARN(&(qedf->dbg_ctx), "request->q is NULL so request "
		   "is not valid, sc_cmd=%p.\n", sc_cmd);
		return;
	}

	fcport = io_req->fcport;

	/*
	 * When flush is active, let the cmds be completed from the cleanup
	 * context
	 */
	if (test_bit(QEDF_RPORT_IN_TARGET_RESET, &fcport->flags) ||
	    (test_bit(QEDF_RPORT_IN_LUN_RESET, &fcport->flags) &&
	     sc_cmd->device->lun == (u64)fcport->lun_reset_lun)) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
			  "Dropping good completion xid=0x%x as fcport is flushing",
			  io_req->xid);
		return;
	}

	qedf_parse_fcp_rsp(io_req, fcp_rsp);

	qedf_unmap_sg_list(qedf, io_req);

	/* Check for FCP transport error */
	if (io_req->fcp_rsp_len > 3 && io_req->fcp_rsp_code) {
		QEDF_ERR(&(qedf->dbg_ctx),
		    "FCP I/O protocol failure xid=0x%x fcp_rsp_len=%d "
		    "fcp_rsp_code=%d.\n", io_req->xid, io_req->fcp_rsp_len,
		    io_req->fcp_rsp_code);
		sc_cmd->result = DID_BUS_BUSY << 16;
		goto out;
	}

	fw_residual_flag = GET_FIELD(cqe->cqe_info.rsp_info.fw_error_flags,
	    FCOE_CQE_RSP_INFO_FW_UNDERRUN);
	if (fw_residual_flag) {
		QEDF_ERR(&qedf->dbg_ctx,
			 "Firmware detected underrun: xid=0x%x fcp_rsp.flags=0x%02x fcp_resid=%d fw_residual=0x%x lba=%02x%02x%02x%02x.\n",
			 io_req->xid, fcp_rsp->rsp_flags.flags,
			 io_req->fcp_resid,
			 cqe->cqe_info.rsp_info.fw_residual, sc_cmd->cmnd[2],
			 sc_cmd->cmnd[3], sc_cmd->cmnd[4], sc_cmd->cmnd[5]);

		if (io_req->cdb_status == 0)
			sc_cmd->result = (DID_ERROR << 16) | io_req->cdb_status;
		else
			sc_cmd->result = (DID_OK << 16) | io_req->cdb_status;

		/*
		 * Set resid to the whole buffer length so we won't try to resue
		 * any previously data.
		 */
		scsi_set_resid(sc_cmd, scsi_bufflen(sc_cmd));
		goto out;
	}

	switch (io_req->fcp_status) {
	case FC_GOOD:
		if (io_req->cdb_status == 0) {
			/* Good I/O completion */
			sc_cmd->result = DID_OK << 16;
		} else {
			refcount = kref_read(&io_req->refcount);
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
			    "%d:0:%d:%lld xid=0x%0x op=0x%02x "
			    "lba=%02x%02x%02x%02x cdb_status=%d "
			    "fcp_resid=0x%x refcount=%d.\n",
			    qedf->lport->host->host_no, sc_cmd->device->id,
			    sc_cmd->device->lun, io_req->xid,
			    sc_cmd->cmnd[0], sc_cmd->cmnd[2], sc_cmd->cmnd[3],
			    sc_cmd->cmnd[4], sc_cmd->cmnd[5],
			    io_req->cdb_status, io_req->fcp_resid,
			    refcount);
			sc_cmd->result = (DID_OK << 16) | io_req->cdb_status;

			if (io_req->cdb_status == SAM_STAT_TASK_SET_FULL ||
			    io_req->cdb_status == SAM_STAT_BUSY) {
				/*
				 * Check whether we need to set retry_delay at
				 * all based on retry_delay module parameter
				 * and the status qualifier.
				 */

				/* Upper 2 bits */
				scope = fcp_rsp->retry_delay_timer & 0xC000;
				/* Lower 14 bits */
				qualifier = fcp_rsp->retry_delay_timer & 0x3FFF;

				if (qedf_retry_delay &&
				    scope > 0 && qualifier > 0 &&
				    qualifier <= 0x3FEF) {
					/* Check we don't go over the max */
					if (qualifier > QEDF_RETRY_DELAY_MAX)
						qualifier =
						    QEDF_RETRY_DELAY_MAX;
					fcport->retry_delay_timestamp =
					    jiffies + (qualifier * HZ / 10);
				}
				/* Record stats */
				if (io_req->cdb_status ==
				    SAM_STAT_TASK_SET_FULL)
					qedf->task_set_fulls++;
				else
					qedf->busy++;
			}
		}
		if (io_req->fcp_resid)
			scsi_set_resid(sc_cmd, io_req->fcp_resid);
		break;
	default:
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO, "fcp_status=%d.\n",
			   io_req->fcp_status);
		break;
	}

out:
	if (qedf_io_tracing)
		qedf_trace_io(fcport, io_req, QEDF_IO_TRACE_RSP);

	/*
	 * We wait till the end of the function to clear the
	 * outstanding bit in case we need to send an abort
	 */
	clear_bit(QEDF_CMD_OUTSTANDING, &io_req->flags);

	io_req->sc_cmd = NULL;
	sc_cmd->SCp.ptr =  NULL;
	sc_cmd->scsi_done(sc_cmd);
	kref_put(&io_req->refcount, qedf_release_cmd);
}