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
typedef  int u8 ;
typedef  void* u32 ;
struct TYPE_9__ {int /*<<< orphan*/  mid_path; } ;
struct TYPE_10__ {TYPE_2__ tx_params; } ;
struct ystorm_fcoe_task_st_ctx {int task_type; TYPE_3__ tx_info_union; void* data_2_trns_rem; int /*<<< orphan*/  sgl_mode; int /*<<< orphan*/  data_desc; int /*<<< orphan*/  sgl_params; } ;
struct TYPE_12__ {int /*<<< orphan*/  rx_id; int /*<<< orphan*/  flags; } ;
struct TYPE_11__ {int task_type; void* glbl_q_num; void* cid; } ;
struct tstorm_fcoe_task_st_ctx {TYPE_5__ read_write; TYPE_4__ read_only; } ;
struct scsi_sgl_task_params {int num_sges; int /*<<< orphan*/  total_buffer_size; } ;
struct mstorm_fcoe_task_st_ctx {void* data_2_trns_rem; int /*<<< orphan*/  flags; int /*<<< orphan*/  data_desc; int /*<<< orphan*/  sgl_params; } ;
struct fcoe_tx_mid_path_params {int dummy; } ;
struct fcoe_task_params {TYPE_7__* sqe; int /*<<< orphan*/  cq_rss_number; scalar_t__ task_type; int /*<<< orphan*/  conn_cid; int /*<<< orphan*/  rx_io_size; int /*<<< orphan*/  tx_io_size; struct e4_fcoe_task_context* context; } ;
struct e4_ustorm_fcoe_task_ag_ctx {void* global_cq_num; } ;
struct TYPE_8__ {int byte0; } ;
struct e4_fcoe_task_context {struct e4_ustorm_fcoe_task_ag_ctx ustorm_ag_context; struct tstorm_fcoe_task_st_ctx tstorm_st_context; struct mstorm_fcoe_task_st_ctx mstorm_st_context; struct ystorm_fcoe_task_st_ctx ystorm_st_context; TYPE_1__ ystorm_ag_context; } ;
struct TYPE_13__ {int /*<<< orphan*/  burst_length; } ;
struct TYPE_14__ {int /*<<< orphan*/  flags; TYPE_6__ additional_info_union; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCOE_RX_ID ; 
 int /*<<< orphan*/  FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_EXP_FIRST_FRAME ; 
 int /*<<< orphan*/  FCOE_WQE_NUM_SGES ; 
 int /*<<< orphan*/  FCOE_WQE_SGL_MODE ; 
 int /*<<< orphan*/  MSTORM_FCOE_TASK_ST_CTX_MP_INCLUDE_FC_HEADER ; 
 int SCSI_FAST_SGL ; 
 int /*<<< orphan*/  SEND_FCOE_MIDPATH ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  YSTORM_FCOE_TASK_ST_CTX_TX_SGL_MODE ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_common_sqe (struct fcoe_task_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_scsi_sgl_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct scsi_sgl_task_params*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct fcoe_tx_mid_path_params*,int) ; 
 int /*<<< orphan*/  memset (struct e4_fcoe_task_context*,int /*<<< orphan*/ ,int) ; 

int init_initiator_midpath_unsolicited_fcoe_task(
	struct fcoe_task_params *task_params,
	struct fcoe_tx_mid_path_params *mid_path_fc_header,
	struct scsi_sgl_task_params *tx_sgl_task_params,
	struct scsi_sgl_task_params *rx_sgl_task_params,
	u8 fw_to_place_fc_header)
{
	struct e4_fcoe_task_context *ctx = task_params->context;
	const u8 val_byte = ctx->ystorm_ag_context.byte0;
	struct e4_ustorm_fcoe_task_ag_ctx *u_ag_ctx;
	struct ystorm_fcoe_task_st_ctx *y_st_ctx;
	struct tstorm_fcoe_task_st_ctx *t_st_ctx;
	struct mstorm_fcoe_task_st_ctx *m_st_ctx;
	u32 val;

	memset(ctx, 0, sizeof(*(ctx)));
	ctx->ystorm_ag_context.byte0 = val_byte;

	/* Init Ystorm */
	y_st_ctx = &ctx->ystorm_st_context;
	init_scsi_sgl_context(&y_st_ctx->sgl_params,
			      &y_st_ctx->data_desc,
			      tx_sgl_task_params);
	SET_FIELD(y_st_ctx->sgl_mode,
		  YSTORM_FCOE_TASK_ST_CTX_TX_SGL_MODE, SCSI_FAST_SGL);
	y_st_ctx->data_2_trns_rem = cpu_to_le32(task_params->tx_io_size);
	y_st_ctx->task_type = (u8)task_params->task_type;
	memcpy(&y_st_ctx->tx_info_union.tx_params.mid_path,
	       mid_path_fc_header, sizeof(struct fcoe_tx_mid_path_params));

	/* Init Mstorm */
	m_st_ctx = &ctx->mstorm_st_context;
	init_scsi_sgl_context(&m_st_ctx->sgl_params,
			      &m_st_ctx->data_desc,
			      rx_sgl_task_params);
	SET_FIELD(m_st_ctx->flags,
		  MSTORM_FCOE_TASK_ST_CTX_MP_INCLUDE_FC_HEADER,
		  fw_to_place_fc_header);
	m_st_ctx->data_2_trns_rem = cpu_to_le32(task_params->rx_io_size);

	/* Init Tstorm */
	t_st_ctx = &ctx->tstorm_st_context;
	t_st_ctx->read_only.cid = cpu_to_le32(task_params->conn_cid);
	val = cpu_to_le32(task_params->cq_rss_number);
	t_st_ctx->read_only.glbl_q_num = val;
	t_st_ctx->read_only.task_type = (u8)task_params->task_type;
	SET_FIELD(t_st_ctx->read_write.flags,
		  FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_EXP_FIRST_FRAME, 1);
	t_st_ctx->read_write.rx_id = cpu_to_le16(FCOE_RX_ID);

	/* Init Ustorm */
	u_ag_ctx = &ctx->ustorm_ag_context;
	u_ag_ctx->global_cq_num = cpu_to_le32(task_params->cq_rss_number);

	/* Init SQE */
	init_common_sqe(task_params, SEND_FCOE_MIDPATH);
	task_params->sqe->additional_info_union.burst_length =
				    tx_sgl_task_params->total_buffer_size;
	SET_FIELD(task_params->sqe->flags,
		  FCOE_WQE_NUM_SGES, tx_sgl_task_params->num_sges);
	SET_FIELD(task_params->sqe->flags, FCOE_WQE_SGL_MODE,
		  SCSI_FAST_SGL);

	return 0;
}