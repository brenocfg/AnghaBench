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
struct TYPE_3__ {void* hi; void* lo; } ;
struct scsi_sgl_task_params {int num_sges; scalar_t__ small_mid_sge; void* total_buffer_size; TYPE_1__ sgl_phys_addr; int /*<<< orphan*/  sgl; int /*<<< orphan*/  ox_id; int /*<<< orphan*/  rx_id; int /*<<< orphan*/  df_ctl; int /*<<< orphan*/  cs_ctl; int /*<<< orphan*/  type; int /*<<< orphan*/  r_ctl; int /*<<< orphan*/  parameter; } ;
struct qedf_rport {int /*<<< orphan*/  dev_type; int /*<<< orphan*/  fw_cid; struct qedf_ctx* qedf; } ;
struct fc_frame_header {int /*<<< orphan*/  fh_ox_id; int /*<<< orphan*/  fh_rx_id; int /*<<< orphan*/  fh_df_ctl; int /*<<< orphan*/  fh_cs_ctl; int /*<<< orphan*/  fh_type; int /*<<< orphan*/  fh_r_ctl; int /*<<< orphan*/  fh_parm_offset; } ;
struct qedf_mp_req {int /*<<< orphan*/  mp_resp_bd_dma; int /*<<< orphan*/  mp_resp_bd; int /*<<< orphan*/  mp_req_bd_dma; int /*<<< orphan*/  mp_req_bd; struct fc_frame_header req_fc_hdr; } ;
struct qedf_ioreq {TYPE_2__* task_params; void* data_xfer_len; int /*<<< orphan*/  xid; struct scsi_sgl_task_params* task; int /*<<< orphan*/  cmd_type; struct qedf_rport* fcport; struct qedf_mp_req mp_req; } ;
struct qedf_ctx {int /*<<< orphan*/  control_requests; int /*<<< orphan*/  dbg_ctx; } ;
struct fcoe_wqe {int dummy; } ;
struct fcoe_tx_mid_path_params {int num_sges; scalar_t__ small_mid_sge; void* total_buffer_size; TYPE_1__ sgl_phys_addr; int /*<<< orphan*/  sgl; int /*<<< orphan*/  ox_id; int /*<<< orphan*/  rx_id; int /*<<< orphan*/  df_ctl; int /*<<< orphan*/  cs_ctl; int /*<<< orphan*/  type; int /*<<< orphan*/  r_ctl; int /*<<< orphan*/  parameter; } ;
struct e4_fcoe_task_context {int num_sges; scalar_t__ small_mid_sge; void* total_buffer_size; TYPE_1__ sgl_phys_addr; int /*<<< orphan*/  sgl; int /*<<< orphan*/  ox_id; int /*<<< orphan*/  rx_id; int /*<<< orphan*/  df_ctl; int /*<<< orphan*/  cs_ctl; int /*<<< orphan*/  type; int /*<<< orphan*/  r_ctl; int /*<<< orphan*/  parameter; } ;
struct TYPE_4__ {int /*<<< orphan*/  is_tape_device; scalar_t__ cq_rss_number; int /*<<< orphan*/  itid; int /*<<< orphan*/  conn_cid; void* rx_io_size; void* tx_io_size; int /*<<< orphan*/  task_type; struct fcoe_wqe* sqe; struct scsi_sgl_task_params* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCOE_TASK_TYPE_MIDPATH ; 
 void* PAGE_SIZE ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDF_LOG_DISC ; 
 void* U64_HI (int /*<<< orphan*/ ) ; 
 void* U64_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  init_initiator_midpath_unsolicited_fcoe_task (TYPE_2__*,struct scsi_sgl_task_params*,struct scsi_sgl_task_params*,struct scsi_sgl_task_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct scsi_sgl_task_params*,int /*<<< orphan*/ ,int) ; 

void qedf_init_mp_task(struct qedf_ioreq *io_req,
	struct e4_fcoe_task_context *task_ctx, struct fcoe_wqe *sqe)
{
	struct qedf_mp_req *mp_req = &(io_req->mp_req);
	struct qedf_rport *fcport = io_req->fcport;
	struct qedf_ctx *qedf = io_req->fcport->qedf;
	struct fc_frame_header *fc_hdr;
	struct fcoe_tx_mid_path_params task_fc_hdr;
	struct scsi_sgl_task_params tx_sgl_task_params;
	struct scsi_sgl_task_params rx_sgl_task_params;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
		  "Initializing MP task for cmd_type=%d\n",
		  io_req->cmd_type);

	qedf->control_requests++;

	memset(&tx_sgl_task_params, 0, sizeof(struct scsi_sgl_task_params));
	memset(&rx_sgl_task_params, 0, sizeof(struct scsi_sgl_task_params));
	memset(task_ctx, 0, sizeof(struct e4_fcoe_task_context));
	memset(&task_fc_hdr, 0, sizeof(struct fcoe_tx_mid_path_params));

	/* Setup the task from io_req for easy reference */
	io_req->task = task_ctx;

	/* Setup the fields for fcoe_task_params */
	io_req->task_params->context = task_ctx;
	io_req->task_params->sqe = sqe;
	io_req->task_params->task_type = FCOE_TASK_TYPE_MIDPATH;
	io_req->task_params->tx_io_size = io_req->data_xfer_len;
	/* rx_io_size tells the f/w how large a response buffer we have */
	io_req->task_params->rx_io_size = PAGE_SIZE;
	io_req->task_params->conn_cid = fcport->fw_cid;
	io_req->task_params->itid = io_req->xid;
	/* Return middle path commands on CQ 0 */
	io_req->task_params->cq_rss_number = 0;
	io_req->task_params->is_tape_device = fcport->dev_type;

	fc_hdr = &(mp_req->req_fc_hdr);
	/* Set OX_ID and RX_ID based on driver task id */
	fc_hdr->fh_ox_id = io_req->xid;
	fc_hdr->fh_rx_id = htons(0xffff);

	/* Set up FC header information */
	task_fc_hdr.parameter = fc_hdr->fh_parm_offset;
	task_fc_hdr.r_ctl = fc_hdr->fh_r_ctl;
	task_fc_hdr.type = fc_hdr->fh_type;
	task_fc_hdr.cs_ctl = fc_hdr->fh_cs_ctl;
	task_fc_hdr.df_ctl = fc_hdr->fh_df_ctl;
	task_fc_hdr.rx_id = fc_hdr->fh_rx_id;
	task_fc_hdr.ox_id = fc_hdr->fh_ox_id;

	/* Set up s/g list parameters for request buffer */
	tx_sgl_task_params.sgl = mp_req->mp_req_bd;
	tx_sgl_task_params.sgl_phys_addr.lo = U64_LO(mp_req->mp_req_bd_dma);
	tx_sgl_task_params.sgl_phys_addr.hi = U64_HI(mp_req->mp_req_bd_dma);
	tx_sgl_task_params.num_sges = 1;
	/* Set PAGE_SIZE for now since sg element is that size ??? */
	tx_sgl_task_params.total_buffer_size = io_req->data_xfer_len;
	tx_sgl_task_params.small_mid_sge = 0;

	/* Set up s/g list parameters for request buffer */
	rx_sgl_task_params.sgl = mp_req->mp_resp_bd;
	rx_sgl_task_params.sgl_phys_addr.lo = U64_LO(mp_req->mp_resp_bd_dma);
	rx_sgl_task_params.sgl_phys_addr.hi = U64_HI(mp_req->mp_resp_bd_dma);
	rx_sgl_task_params.num_sges = 1;
	/* Set PAGE_SIZE for now since sg element is that size ??? */
	rx_sgl_task_params.total_buffer_size = PAGE_SIZE;
	rx_sgl_task_params.small_mid_sge = 0;


	/*
	 * Last arg is 0 as previous code did not set that we wanted the
	 * fc header information.
	 */
	init_initiator_midpath_unsolicited_fcoe_task(io_req->task_params,
						     &task_fc_hdr,
						     &tx_sgl_task_params,
						     &rx_sgl_task_params, 0);
}