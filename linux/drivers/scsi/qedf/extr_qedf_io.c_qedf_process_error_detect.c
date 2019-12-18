#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qedf_ioreq {int /*<<< orphan*/  abts_done; TYPE_2__* fcport; int /*<<< orphan*/  xid; } ;
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; scalar_t__ stop_io_on_error; } ;
struct TYPE_7__ {int /*<<< orphan*/  rx_id; int /*<<< orphan*/  rx_buf_off; int /*<<< orphan*/  tx_buf_off; int /*<<< orphan*/  err_warn_bitmap_lo; int /*<<< orphan*/  err_warn_bitmap_hi; } ;
struct TYPE_8__ {TYPE_3__ err_info; } ;
struct fcoe_cqe {TYPE_4__ cqe_info; } ;
struct TYPE_6__ {TYPE_1__* qedf; } ;
struct TYPE_5__ {int /*<<< orphan*/  dbg_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct qedf_ioreq*) ; 
 int /*<<< orphan*/  QEDF_LOG_IO ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int qedf_initiate_abts (struct qedf_ioreq*,int) ; 
 int /*<<< orphan*/  qedf_stop_all_io (struct qedf_ctx*) ; 

void qedf_process_error_detect(struct qedf_ctx *qedf, struct fcoe_cqe *cqe,
	struct qedf_ioreq *io_req)
{
	int rval;

	if (!cqe) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
			  "cqe is NULL for io_req %p\n", io_req);
		return;
	}

	QEDF_ERR(&(io_req->fcport->qedf->dbg_ctx), "Error detection CQE, "
		  "xid=0x%x\n", io_req->xid);
	QEDF_ERR(&(io_req->fcport->qedf->dbg_ctx),
		  "err_warn_bitmap=%08x:%08x\n",
		  le32_to_cpu(cqe->cqe_info.err_info.err_warn_bitmap_hi),
		  le32_to_cpu(cqe->cqe_info.err_info.err_warn_bitmap_lo));
	QEDF_ERR(&(io_req->fcport->qedf->dbg_ctx), "tx_buff_off=%08x, "
		  "rx_buff_off=%08x, rx_id=%04x\n",
		  le32_to_cpu(cqe->cqe_info.err_info.tx_buf_off),
		  le32_to_cpu(cqe->cqe_info.err_info.rx_buf_off),
		  le32_to_cpu(cqe->cqe_info.err_info.rx_id));

	if (qedf->stop_io_on_error) {
		qedf_stop_all_io(qedf);
		return;
	}

	init_completion(&io_req->abts_done);
	rval = qedf_initiate_abts(io_req, true);
	if (rval)
		QEDF_ERR(&(qedf->dbg_ctx), "Failed to queue ABTS.\n");
}