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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
struct scsi_sgl_task_params {int dummy; } ;
struct scsi_cmnd {scalar_t__ sc_data_direction; } ;
struct regpair {void* hi; void* lo; } ;
struct qedf_rport {int /*<<< orphan*/  dev_type; int /*<<< orphan*/  fw_cid; struct qedf_ctx* qedf; } ;
struct qedf_ioreq {scalar_t__ cmd_type; scalar_t__ sge_type; int /*<<< orphan*/  task_retry_identifier; struct e4_fcoe_task_context* sgl_task_params; struct e4_fcoe_task_context* task_params; int /*<<< orphan*/  sense_buffer_dma; struct scsi_cmnd* sc_cmd; int /*<<< orphan*/  xid; void* data_xfer_len; struct e4_fcoe_task_context* task; struct io_bdt* bd_tbl; } ;
struct qedf_ctx {int num_queues; int /*<<< orphan*/  fast_sge_ios; int /*<<< orphan*/  slow_sge_ios; } ;
struct io_bdt {int bd_valid; int /*<<< orphan*/  bd_tbl_dma; int /*<<< orphan*/  bd_tbl; } ;
struct fcp_cmnd {int dummy; } ;
struct fcoe_wqe {int dummy; } ;
struct fcoe_task_params {int dummy; } ;
struct fc_lport {int dummy; } ;
struct TYPE_2__ {void* hi; void* lo; } ;
struct e4_fcoe_task_context {int task_type; int cq_rss_number; int num_sges; int small_mid_sge; int /*<<< orphan*/  total_buffer_size; TYPE_1__ sgl_phys_addr; int /*<<< orphan*/  sgl; int /*<<< orphan*/  is_tape_device; int /*<<< orphan*/  itid; int /*<<< orphan*/  conn_cid; void* rx_io_size; void* tx_io_size; struct fcoe_wqe* sqe; struct e4_fcoe_task_context* context; } ;
typedef  enum fcoe_task_type { ____Placeholder_fcoe_task_type } fcoe_task_type ;

/* Variables and functions */
 scalar_t__ DMA_TO_DEVICE ; 
 int FCOE_TASK_TYPE_READ_INITIATOR ; 
 int FCOE_TASK_TYPE_WRITE_INITIATOR ; 
 scalar_t__ QEDF_IOREQ_SLOW_SGE ; 
 scalar_t__ QEDF_TASK_MGMT_CMD ; 
 void* U64_HI (int /*<<< orphan*/ ) ; 
 void* U64_LO (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (void*) ; 
 int /*<<< orphan*/  init_initiator_rw_fcoe_task (struct e4_fcoe_task_context*,struct e4_fcoe_task_context*,struct regpair,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void**,int) ; 
 int /*<<< orphan*/  memset (struct e4_fcoe_task_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qedf_build_fcp_cmnd (struct qedf_ioreq*,struct fcp_cmnd*) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 int smp_processor_id () ; 

__attribute__((used)) static void  qedf_init_task(struct qedf_rport *fcport, struct fc_lport *lport,
	struct qedf_ioreq *io_req, struct e4_fcoe_task_context *task_ctx,
	struct fcoe_wqe *sqe)
{
	enum fcoe_task_type task_type;
	struct scsi_cmnd *sc_cmd = io_req->sc_cmd;
	struct io_bdt *bd_tbl = io_req->bd_tbl;
	u8 fcp_cmnd[32];
	u32 tmp_fcp_cmnd[8];
	int bd_count = 0;
	struct qedf_ctx *qedf = fcport->qedf;
	uint16_t cq_idx = smp_processor_id() % qedf->num_queues;
	struct regpair sense_data_buffer_phys_addr;
	u32 tx_io_size = 0;
	u32 rx_io_size = 0;
	int i, cnt;

	/* Note init_initiator_rw_fcoe_task memsets the task context */
	io_req->task = task_ctx;
	memset(task_ctx, 0, sizeof(struct e4_fcoe_task_context));
	memset(io_req->task_params, 0, sizeof(struct fcoe_task_params));
	memset(io_req->sgl_task_params, 0, sizeof(struct scsi_sgl_task_params));

	/* Set task type bassed on DMA directio of command */
	if (io_req->cmd_type == QEDF_TASK_MGMT_CMD) {
		task_type = FCOE_TASK_TYPE_READ_INITIATOR;
	} else {
		if (sc_cmd->sc_data_direction == DMA_TO_DEVICE) {
			task_type = FCOE_TASK_TYPE_WRITE_INITIATOR;
			tx_io_size = io_req->data_xfer_len;
		} else {
			task_type = FCOE_TASK_TYPE_READ_INITIATOR;
			rx_io_size = io_req->data_xfer_len;
		}
	}

	/* Setup the fields for fcoe_task_params */
	io_req->task_params->context = task_ctx;
	io_req->task_params->sqe = sqe;
	io_req->task_params->task_type = task_type;
	io_req->task_params->tx_io_size = tx_io_size;
	io_req->task_params->rx_io_size = rx_io_size;
	io_req->task_params->conn_cid = fcport->fw_cid;
	io_req->task_params->itid = io_req->xid;
	io_req->task_params->cq_rss_number = cq_idx;
	io_req->task_params->is_tape_device = fcport->dev_type;

	/* Fill in information for scatter/gather list */
	if (io_req->cmd_type != QEDF_TASK_MGMT_CMD) {
		bd_count = bd_tbl->bd_valid;
		io_req->sgl_task_params->sgl = bd_tbl->bd_tbl;
		io_req->sgl_task_params->sgl_phys_addr.lo =
			U64_LO(bd_tbl->bd_tbl_dma);
		io_req->sgl_task_params->sgl_phys_addr.hi =
			U64_HI(bd_tbl->bd_tbl_dma);
		io_req->sgl_task_params->num_sges = bd_count;
		io_req->sgl_task_params->total_buffer_size =
		    scsi_bufflen(io_req->sc_cmd);
		if (io_req->sge_type == QEDF_IOREQ_SLOW_SGE)
			io_req->sgl_task_params->small_mid_sge = 1;
		else
			io_req->sgl_task_params->small_mid_sge = 0;
	}

	/* Fill in physical address of sense buffer */
	sense_data_buffer_phys_addr.lo = U64_LO(io_req->sense_buffer_dma);
	sense_data_buffer_phys_addr.hi = U64_HI(io_req->sense_buffer_dma);

	/* fill FCP_CMND IU */
	qedf_build_fcp_cmnd(io_req, (struct fcp_cmnd *)tmp_fcp_cmnd);

	/* Swap fcp_cmnd since FC is big endian */
	cnt = sizeof(struct fcp_cmnd) / sizeof(u32);
	for (i = 0; i < cnt; i++) {
		tmp_fcp_cmnd[i] = cpu_to_be32(tmp_fcp_cmnd[i]);
	}
	memcpy(fcp_cmnd, tmp_fcp_cmnd, sizeof(struct fcp_cmnd));

	init_initiator_rw_fcoe_task(io_req->task_params,
				    io_req->sgl_task_params,
				    sense_data_buffer_phys_addr,
				    io_req->task_retry_identifier, fcp_cmnd);

	/* Increment SGL type counters */
	if (io_req->sge_type == QEDF_IOREQ_SLOW_SGE)
		qedf->slow_sge_ios++;
	else
		qedf->fast_sge_ios++;
}