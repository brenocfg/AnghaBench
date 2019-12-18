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
typedef  int u8 ;
typedef  int u64 ;
struct qedf_rport {scalar_t__ dev_type; TYPE_1__* qedf; } ;
struct qedf_ioreq {int /*<<< orphan*/  abts_done; scalar_t__ rx_id; scalar_t__ tx_buf_off; scalar_t__ rx_buf_off; int /*<<< orphan*/  flags; struct qedf_rport* fcport; int /*<<< orphan*/  xid; } ;
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; } ;
struct TYPE_5__ {scalar_t__ rx_id; scalar_t__ tx_buf_off; scalar_t__ rx_buf_off; scalar_t__ err_warn_bitmap_lo; scalar_t__ err_warn_bitmap_hi; } ;
struct TYPE_6__ {TYPE_2__ err_info; } ;
struct fcoe_cqe {TYPE_3__ cqe_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  dbg_ctx; } ;

/* Variables and functions */
 int FCOE_WARNING_CODE_REC_TOV_TIMER_EXPIRATION ; 
 int /*<<< orphan*/  QEDF_CMD_SRR_SENT ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct qedf_ioreq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDF_LOG_IO ; 
 scalar_t__ QEDF_RPORT_TYPE_TAPE ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 int qedf_initiate_abts (struct qedf_ioreq*,int) ; 
 int qedf_send_rec (struct qedf_ioreq*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qedf_process_warning_compl(struct qedf_ctx *qedf, struct fcoe_cqe *cqe,
	struct qedf_ioreq *io_req)
{
	int rval, i;
	struct qedf_rport *fcport = io_req->fcport;
	u64 err_warn_bit_map;
	u8 err_warn = 0xff;

	if (!cqe) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
			  "cqe is NULL for io_req %p xid=0x%x\n",
			  io_req, io_req->xid);
		return;
	}

	QEDF_ERR(&(io_req->fcport->qedf->dbg_ctx), "Warning CQE, "
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

	/* Normalize the error bitmap value to an just an unsigned int */
	err_warn_bit_map = (u64)
	    ((u64)cqe->cqe_info.err_info.err_warn_bitmap_hi << 32) |
	    (u64)cqe->cqe_info.err_info.err_warn_bitmap_lo;
	for (i = 0; i < 64; i++) {
		if (err_warn_bit_map & (u64)((u64)1 << i)) {
			err_warn = i;
			break;
		}
	}

	/* Check if REC TOV expired if this is a tape device */
	if (fcport->dev_type == QEDF_RPORT_TYPE_TAPE) {
		if (err_warn ==
		    FCOE_WARNING_CODE_REC_TOV_TIMER_EXPIRATION) {
			QEDF_ERR(&(qedf->dbg_ctx), "REC timer expired.\n");
			if (!test_bit(QEDF_CMD_SRR_SENT, &io_req->flags)) {
				io_req->rx_buf_off =
				    cqe->cqe_info.err_info.rx_buf_off;
				io_req->tx_buf_off =
				    cqe->cqe_info.err_info.tx_buf_off;
				io_req->rx_id = cqe->cqe_info.err_info.rx_id;
				rval = qedf_send_rec(io_req);
				/*
				 * We only want to abort the io_req if we
				 * can't queue the REC command as we want to
				 * keep the exchange open for recovery.
				 */
				if (rval)
					goto send_abort;
			}
			return;
		}
	}

send_abort:
	init_completion(&io_req->abts_done);
	rval = qedf_initiate_abts(io_req, true);
	if (rval)
		QEDF_ERR(&(qedf->dbg_ctx), "Failed to queue ABTS.\n");
}