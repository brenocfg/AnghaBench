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
typedef  int u32 ;
typedef  size_t u16 ;
struct qedf_rport {int /*<<< orphan*/  free_sqes; int /*<<< orphan*/  flags; } ;
struct qedf_ioreq {int /*<<< orphan*/  cmd_type; struct qedf_rport* fcport; } ;
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; TYPE_1__* cmd_mgr; } ;
struct fcoe_cqe {int cqe_data; } ;
struct TYPE_2__ {struct qedf_ioreq* cmds; } ;

/* Variables and functions */
#define  FCOE_ABTS_CQE_TYPE 139 
 int FCOE_CQE_CQE_TYPE_MASK ; 
 int FCOE_CQE_CQE_TYPE_SHIFT ; 
 size_t FCOE_CQE_TASK_ID_MASK ; 
#define  FCOE_DUMMY_CQE_TYPE 138 
#define  FCOE_ERROR_DETECTION_CQE_TYPE 137 
#define  FCOE_EXCH_CLEANUP_CQE_TYPE 136 
#define  FCOE_GOOD_COMPLETION_CQE_TYPE 135 
#define  FCOE_LOCAL_COMP_CQE_TYPE 134 
#define  FCOE_WARNING_CQE_TYPE 133 
#define  MAX_FCOE_CQE_TYPE 132 
#define  QEDF_ELS 131 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QEDF_LOG_IO ; 
 int /*<<< orphan*/  QEDF_RPORT_SESSION_READY ; 
#define  QEDF_SCSI_CMD 130 
#define  QEDF_SEQ_CLEANUP 129 
#define  QEDF_TASK_MGMT_CMD 128 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qedf_process_abts_compl (struct qedf_ctx*,struct fcoe_cqe*,struct qedf_ioreq*) ; 
 int /*<<< orphan*/  qedf_process_cleanup_compl (struct qedf_ctx*,struct fcoe_cqe*,struct qedf_ioreq*) ; 
 int /*<<< orphan*/  qedf_process_els_compl (struct qedf_ctx*,struct fcoe_cqe*,struct qedf_ioreq*) ; 
 int /*<<< orphan*/  qedf_process_error_detect (struct qedf_ctx*,struct fcoe_cqe*,struct qedf_ioreq*) ; 
 int /*<<< orphan*/  qedf_process_seq_cleanup_compl (struct qedf_ctx*,struct fcoe_cqe*,struct qedf_ioreq*) ; 
 int /*<<< orphan*/  qedf_process_tmf_compl (struct qedf_ctx*,struct fcoe_cqe*,struct qedf_ioreq*) ; 
 int /*<<< orphan*/  qedf_process_warning_compl (struct qedf_ctx*,struct fcoe_cqe*,struct qedf_ioreq*) ; 
 int /*<<< orphan*/  qedf_scsi_completion (struct qedf_ctx*,struct fcoe_cqe*,struct qedf_ioreq*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qedf_process_cqe(struct qedf_ctx *qedf, struct fcoe_cqe *cqe)
{
	u16 xid;
	struct qedf_ioreq *io_req;
	struct qedf_rport *fcport;
	u32 comp_type;

	comp_type = (cqe->cqe_data >> FCOE_CQE_CQE_TYPE_SHIFT) &
	    FCOE_CQE_CQE_TYPE_MASK;

	xid = cqe->cqe_data & FCOE_CQE_TASK_ID_MASK;
	io_req = &qedf->cmd_mgr->cmds[xid];

	/* Completion not for a valid I/O anymore so just return */
	if (!io_req) {
		QEDF_ERR(&qedf->dbg_ctx,
			 "io_req is NULL for xid=0x%x.\n", xid);
		return;
	}

	fcport = io_req->fcport;

	if (fcport == NULL) {
		QEDF_ERR(&qedf->dbg_ctx,
			 "fcport is NULL for xid=0x%x io_req=%p.\n",
			 xid, io_req);
		return;
	}

	/*
	 * Check that fcport is offloaded.  If it isn't then the spinlock
	 * isn't valid and shouldn't be taken. We should just return.
	 */
	if (!test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags)) {
		QEDF_ERR(&qedf->dbg_ctx,
			 "Session not offloaded yet, fcport = %p.\n", fcport);
		return;
	}


	switch (comp_type) {
	case FCOE_GOOD_COMPLETION_CQE_TYPE:
		atomic_inc(&fcport->free_sqes);
		switch (io_req->cmd_type) {
		case QEDF_SCSI_CMD:
			qedf_scsi_completion(qedf, cqe, io_req);
			break;
		case QEDF_ELS:
			qedf_process_els_compl(qedf, cqe, io_req);
			break;
		case QEDF_TASK_MGMT_CMD:
			qedf_process_tmf_compl(qedf, cqe, io_req);
			break;
		case QEDF_SEQ_CLEANUP:
			qedf_process_seq_cleanup_compl(qedf, cqe, io_req);
			break;
		}
		break;
	case FCOE_ERROR_DETECTION_CQE_TYPE:
		atomic_inc(&fcport->free_sqes);
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Error detect CQE.\n");
		qedf_process_error_detect(qedf, cqe, io_req);
		break;
	case FCOE_EXCH_CLEANUP_CQE_TYPE:
		atomic_inc(&fcport->free_sqes);
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Cleanup CQE.\n");
		qedf_process_cleanup_compl(qedf, cqe, io_req);
		break;
	case FCOE_ABTS_CQE_TYPE:
		atomic_inc(&fcport->free_sqes);
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Abort CQE.\n");
		qedf_process_abts_compl(qedf, cqe, io_req);
		break;
	case FCOE_DUMMY_CQE_TYPE:
		atomic_inc(&fcport->free_sqes);
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Dummy CQE.\n");
		break;
	case FCOE_LOCAL_COMP_CQE_TYPE:
		atomic_inc(&fcport->free_sqes);
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Local completion CQE.\n");
		break;
	case FCOE_WARNING_CQE_TYPE:
		atomic_inc(&fcport->free_sqes);
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Warning CQE.\n");
		qedf_process_warning_compl(qedf, cqe, io_req);
		break;
	case MAX_FCOE_CQE_TYPE:
		atomic_inc(&fcport->free_sqes);
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Max FCoE CQE.\n");
		break;
	default:
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Default CQE.\n");
		break;
	}
}