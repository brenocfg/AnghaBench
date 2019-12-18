#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  void* u32 ;
typedef  size_t u16 ;
typedef  int /*<<< orphan*/  tx_sgl_task_params ;
typedef  int /*<<< orphan*/  task_params ;
struct TYPE_7__ {void* hi; void* lo; } ;
struct TYPE_6__ {void* hi; void* lo; } ;
struct TYPE_10__ {void* hi; void* lo; } ;
struct scsi_sgl_task_params {int num_sges; int small_mid_sge; int initial_r2t; int immediate_data; size_t conn_icid; int itid; size_t cq_rss_number; scalar_t__ tx_io_size; scalar_t__ rx_io_size; struct scsi_sgl_task_params* sqe; struct scsi_sgl_task_params* context; TYPE_2__ sense_data_buffer_phys_addr; int /*<<< orphan*/  max_burst_length; int /*<<< orphan*/  max_send_pdu_length; int /*<<< orphan*/  first_burst_length; void* total_buffer_size; TYPE_1__ sgl_phys_addr; int /*<<< orphan*/  sgl; scalar_t__ cdb; int /*<<< orphan*/  hdr_first_byte; void* cmd_sn; int /*<<< orphan*/  hdr_second_dword; int /*<<< orphan*/  expected_transfer_length; int /*<<< orphan*/  itt; TYPE_5__ lun; int /*<<< orphan*/  flags_attr; } ;
struct scsi_lun {int dummy; } ;
struct scsi_initiator_cmd_params {int num_sges; int small_mid_sge; int initial_r2t; int immediate_data; size_t conn_icid; int itid; size_t cq_rss_number; scalar_t__ tx_io_size; scalar_t__ rx_io_size; struct scsi_initiator_cmd_params* sqe; struct scsi_initiator_cmd_params* context; TYPE_2__ sense_data_buffer_phys_addr; int /*<<< orphan*/  max_burst_length; int /*<<< orphan*/  max_send_pdu_length; int /*<<< orphan*/  first_burst_length; void* total_buffer_size; TYPE_1__ sgl_phys_addr; int /*<<< orphan*/  sgl; scalar_t__ cdb; int /*<<< orphan*/  hdr_first_byte; void* cmd_sn; int /*<<< orphan*/  hdr_second_dword; int /*<<< orphan*/  expected_transfer_length; int /*<<< orphan*/  itt; TYPE_5__ lun; int /*<<< orphan*/  flags_attr; } ;
struct scsi_cmnd {scalar_t__ sc_data_direction; TYPE_4__* device; } ;
struct qedi_endpoint {struct scsi_sgl_task_params* sq; } ;
struct qedi_ctx {size_t num_queues; int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/  tasks; } ;
struct qedi_conn {int /*<<< orphan*/  list_lock; int /*<<< orphan*/  active_cmd_count; int /*<<< orphan*/  active_cmd_list; scalar_t__ iscsi_conn_id; struct iscsi_cls_conn* cls_conn; struct qedi_endpoint* ep; } ;
struct TYPE_8__ {int sge_valid; scalar_t__ sge_tbl_dma; int /*<<< orphan*/  sge_tbl; } ;
struct qedi_cmd {int task_id; int io_cmd_in_list; int /*<<< orphan*/  io_cmd; TYPE_3__ io_tbl; scalar_t__ use_slowpath; scalar_t__ sense_buffer_dma; } ;
struct iscsi_wqe {int dummy; } ;
struct iscsi_task_params {int num_sges; int small_mid_sge; int initial_r2t; int immediate_data; size_t conn_icid; int itid; size_t cq_rss_number; scalar_t__ tx_io_size; scalar_t__ rx_io_size; struct iscsi_task_params* sqe; struct iscsi_task_params* context; TYPE_2__ sense_data_buffer_phys_addr; int /*<<< orphan*/  max_burst_length; int /*<<< orphan*/  max_send_pdu_length; int /*<<< orphan*/  first_burst_length; void* total_buffer_size; TYPE_1__ sgl_phys_addr; int /*<<< orphan*/  sgl; scalar_t__ cdb; int /*<<< orphan*/  hdr_first_byte; void* cmd_sn; int /*<<< orphan*/  hdr_second_dword; int /*<<< orphan*/  expected_transfer_length; int /*<<< orphan*/  itt; TYPE_5__ lun; int /*<<< orphan*/  flags_attr; } ;
struct iscsi_task {int /*<<< orphan*/  itt; scalar_t__ hdr; struct scsi_cmnd* sc; struct qedi_cmd* dd_data; struct iscsi_conn* conn; } ;
struct iscsi_session {scalar_t__ imm_data_en; scalar_t__ initial_r2t_en; int /*<<< orphan*/  max_burst; int /*<<< orphan*/  first_burst; int /*<<< orphan*/  cls_session; } ;
struct iscsi_scsi_req {scalar_t__* cdb; void* cmdsn; int /*<<< orphan*/  opcode; int /*<<< orphan*/  dlength; int /*<<< orphan*/  data_length; } ;
struct iscsi_conn_params {int num_sges; int small_mid_sge; int initial_r2t; int immediate_data; size_t conn_icid; int itid; size_t cq_rss_number; scalar_t__ tx_io_size; scalar_t__ rx_io_size; struct iscsi_conn_params* sqe; struct iscsi_conn_params* context; TYPE_2__ sense_data_buffer_phys_addr; int /*<<< orphan*/  max_burst_length; int /*<<< orphan*/  max_send_pdu_length; int /*<<< orphan*/  first_burst_length; void* total_buffer_size; TYPE_1__ sgl_phys_addr; int /*<<< orphan*/  sgl; scalar_t__ cdb; int /*<<< orphan*/  hdr_first_byte; void* cmd_sn; int /*<<< orphan*/  hdr_second_dword; int /*<<< orphan*/  expected_transfer_length; int /*<<< orphan*/  itt; TYPE_5__ lun; int /*<<< orphan*/  flags_attr; } ;
struct iscsi_conn {struct iscsi_session* session; int /*<<< orphan*/  max_xmit_dlength; struct qedi_conn* dd_data; } ;
struct iscsi_cmd_hdr {int num_sges; int small_mid_sge; int initial_r2t; int immediate_data; size_t conn_icid; int itid; size_t cq_rss_number; scalar_t__ tx_io_size; scalar_t__ rx_io_size; struct iscsi_cmd_hdr* sqe; struct iscsi_cmd_hdr* context; TYPE_2__ sense_data_buffer_phys_addr; int /*<<< orphan*/  max_burst_length; int /*<<< orphan*/  max_send_pdu_length; int /*<<< orphan*/  first_burst_length; void* total_buffer_size; TYPE_1__ sgl_phys_addr; int /*<<< orphan*/  sgl; scalar_t__ cdb; int /*<<< orphan*/  hdr_first_byte; void* cmd_sn; int /*<<< orphan*/  hdr_second_dword; int /*<<< orphan*/  expected_transfer_length; int /*<<< orphan*/  itt; TYPE_5__ lun; int /*<<< orphan*/  flags_attr; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct e4_iscsi_task_context {int num_sges; int small_mid_sge; int initial_r2t; int immediate_data; size_t conn_icid; int itid; size_t cq_rss_number; scalar_t__ tx_io_size; scalar_t__ rx_io_size; struct e4_iscsi_task_context* sqe; struct e4_iscsi_task_context* context; TYPE_2__ sense_data_buffer_phys_addr; int /*<<< orphan*/  max_burst_length; int /*<<< orphan*/  max_send_pdu_length; int /*<<< orphan*/  first_burst_length; void* total_buffer_size; TYPE_1__ sgl_phys_addr; int /*<<< orphan*/  sgl; scalar_t__ cdb; int /*<<< orphan*/  hdr_first_byte; void* cmd_sn; int /*<<< orphan*/  hdr_second_dword; int /*<<< orphan*/  expected_transfer_length; int /*<<< orphan*/  itt; TYPE_5__ lun; int /*<<< orphan*/  flags_attr; } ;
struct Scsi_Host {int dummy; } ;
typedef  int s16 ;
typedef  int /*<<< orphan*/  rx_sgl_task_params ;
typedef  enum iscsi_task_type { ____Placeholder_iscsi_task_type } iscsi_task_type ;
typedef  int /*<<< orphan*/  conn_params ;
typedef  int /*<<< orphan*/  cmd_pdu_header ;
typedef  int /*<<< orphan*/  cmd_params ;
struct TYPE_9__ {int /*<<< orphan*/  lun; } ;

/* Variables and functions */
 scalar_t__ DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int ISCSI_ATTR_SIMPLE ; 
 int /*<<< orphan*/  ISCSI_CMD_HDR_ATTR ; 
 int /*<<< orphan*/  ISCSI_CMD_HDR_READ ; 
 int /*<<< orphan*/  ISCSI_CMD_HDR_WRITE ; 
 int ISCSI_TASK_TYPE_INITIATOR_READ ; 
 int ISCSI_TASK_TYPE_INITIATOR_WRITE ; 
 int MAX_ISCSI_TASK_TYPE ; 
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,char*,size_t,void*,void*,void*) ; 
 int /*<<< orphan*/  QEDI_LOG_IO ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ TEST_UNIT_READY ; 
 void* be32_to_cpu (void*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_itt (int /*<<< orphan*/ ) ; 
 int init_initiator_rw_iscsi_task (struct scsi_sgl_task_params*,struct scsi_sgl_task_params*,struct scsi_sgl_task_params*,struct scsi_sgl_task_params*,struct scsi_sgl_task_params*,struct scsi_sgl_task_params*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  int_to_scsilun (int /*<<< orphan*/ ,struct scsi_lun*) ; 
 struct qedi_ctx* iscsi_host_priv (struct Scsi_Host*) ; 
 struct Scsi_Host* iscsi_session_to_shost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct scsi_sgl_task_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntoh24 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedi_cpy_scsi_cdb (struct scsi_cmnd*,void**) ; 
 int qedi_get_task_idx (struct qedi_ctx*) ; 
 scalar_t__ qedi_get_task_mem (int /*<<< orphan*/ *,int) ; 
 size_t qedi_get_wqe_idx (struct qedi_conn*) ; 
 int /*<<< orphan*/  qedi_iscsi_map_sg_list (struct qedi_cmd*) ; 
 int /*<<< orphan*/  qedi_ring_doorbell (struct qedi_conn*) ; 
 int /*<<< orphan*/  qedi_set_itt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedi_update_itt_map (struct qedi_ctx*,int,int /*<<< orphan*/ ,struct qedi_cmd*) ; 
 void* scsi_bufflen (struct scsi_cmnd*) ; 
 size_t smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int qedi_iscsi_send_ioreq(struct iscsi_task *task)
{
	struct iscsi_conn *conn = task->conn;
	struct iscsi_session *session = conn->session;
	struct Scsi_Host *shost = iscsi_session_to_shost(session->cls_session);
	struct qedi_ctx *qedi = iscsi_host_priv(shost);
	struct qedi_conn *qedi_conn = conn->dd_data;
	struct qedi_cmd *cmd = task->dd_data;
	struct scsi_cmnd *sc = task->sc;
	struct iscsi_cmd_hdr cmd_pdu_header;
	struct scsi_sgl_task_params tx_sgl_task_params;
	struct scsi_sgl_task_params rx_sgl_task_params;
	struct scsi_sgl_task_params *prx_sgl = NULL;
	struct scsi_sgl_task_params *ptx_sgl = NULL;
	struct iscsi_task_params task_params;
	struct iscsi_conn_params conn_params;
	struct scsi_initiator_cmd_params cmd_params;
	struct e4_iscsi_task_context *fw_task_ctx;
	struct iscsi_cls_conn *cls_conn;
	struct iscsi_scsi_req *hdr = (struct iscsi_scsi_req *)task->hdr;
	enum iscsi_task_type task_type = MAX_ISCSI_TASK_TYPE;
	struct qedi_endpoint *ep;
	u32 scsi_lun[2];
	s16 tid = 0;
	u16 sq_idx = 0;
	u16 cq_idx;
	int rval = 0;

	ep = qedi_conn->ep;
	cls_conn = qedi_conn->cls_conn;
	conn = cls_conn->dd_data;

	qedi_iscsi_map_sg_list(cmd);
	int_to_scsilun(sc->device->lun, (struct scsi_lun *)scsi_lun);

	tid = qedi_get_task_idx(qedi);
	if (tid == -1)
		return -ENOMEM;

	fw_task_ctx =
	     (struct e4_iscsi_task_context *)qedi_get_task_mem(&qedi->tasks,
							       tid);
	memset(fw_task_ctx, 0, sizeof(struct e4_iscsi_task_context));

	cmd->task_id = tid;

	memset(&task_params, 0, sizeof(task_params));
	memset(&cmd_pdu_header, 0, sizeof(cmd_pdu_header));
	memset(&tx_sgl_task_params, 0, sizeof(tx_sgl_task_params));
	memset(&rx_sgl_task_params, 0, sizeof(rx_sgl_task_params));
	memset(&conn_params, 0, sizeof(conn_params));
	memset(&cmd_params, 0, sizeof(cmd_params));

	cq_idx = smp_processor_id() % qedi->num_queues;
	/* Update header info */
	SET_FIELD(cmd_pdu_header.flags_attr, ISCSI_CMD_HDR_ATTR,
		  ISCSI_ATTR_SIMPLE);
	if (hdr->cdb[0] != TEST_UNIT_READY) {
		if (sc->sc_data_direction == DMA_TO_DEVICE) {
			SET_FIELD(cmd_pdu_header.flags_attr,
				  ISCSI_CMD_HDR_WRITE, 1);
			task_type = ISCSI_TASK_TYPE_INITIATOR_WRITE;
		} else {
			SET_FIELD(cmd_pdu_header.flags_attr,
				  ISCSI_CMD_HDR_READ, 1);
			task_type = ISCSI_TASK_TYPE_INITIATOR_READ;
		}
	}

	cmd_pdu_header.lun.lo = be32_to_cpu(scsi_lun[0]);
	cmd_pdu_header.lun.hi = be32_to_cpu(scsi_lun[1]);

	qedi_update_itt_map(qedi, tid, task->itt, cmd);
	cmd_pdu_header.itt = qedi_set_itt(tid, get_itt(task->itt));
	cmd_pdu_header.expected_transfer_length = cpu_to_be32(hdr->data_length);
	cmd_pdu_header.hdr_second_dword = ntoh24(hdr->dlength);
	cmd_pdu_header.cmd_sn = be32_to_cpu(hdr->cmdsn);
	cmd_pdu_header.hdr_first_byte = hdr->opcode;
	qedi_cpy_scsi_cdb(sc, (u32 *)cmd_pdu_header.cdb);

	/* Fill tx AHS and rx buffer */
	if (task_type == ISCSI_TASK_TYPE_INITIATOR_WRITE) {
		tx_sgl_task_params.sgl = cmd->io_tbl.sge_tbl;
		tx_sgl_task_params.sgl_phys_addr.lo =
						 (u32)(cmd->io_tbl.sge_tbl_dma);
		tx_sgl_task_params.sgl_phys_addr.hi =
				      (u32)((u64)cmd->io_tbl.sge_tbl_dma >> 32);
		tx_sgl_task_params.total_buffer_size = scsi_bufflen(sc);
		tx_sgl_task_params.num_sges = cmd->io_tbl.sge_valid;
		if (cmd->use_slowpath)
			tx_sgl_task_params.small_mid_sge = true;
	} else if (task_type == ISCSI_TASK_TYPE_INITIATOR_READ) {
		rx_sgl_task_params.sgl = cmd->io_tbl.sge_tbl;
		rx_sgl_task_params.sgl_phys_addr.lo =
						 (u32)(cmd->io_tbl.sge_tbl_dma);
		rx_sgl_task_params.sgl_phys_addr.hi =
				      (u32)((u64)cmd->io_tbl.sge_tbl_dma >> 32);
		rx_sgl_task_params.total_buffer_size = scsi_bufflen(sc);
		rx_sgl_task_params.num_sges = cmd->io_tbl.sge_valid;
	}

	/* Add conn param */
	conn_params.first_burst_length = conn->session->first_burst;
	conn_params.max_send_pdu_length = conn->max_xmit_dlength;
	conn_params.max_burst_length = conn->session->max_burst;
	if (conn->session->initial_r2t_en)
		conn_params.initial_r2t = true;
	if (conn->session->imm_data_en)
		conn_params.immediate_data = true;

	/* Add cmd params */
	cmd_params.sense_data_buffer_phys_addr.lo = (u32)cmd->sense_buffer_dma;
	cmd_params.sense_data_buffer_phys_addr.hi =
					(u32)((u64)cmd->sense_buffer_dma >> 32);
	/* Fill fw input params */
	task_params.context = fw_task_ctx;
	task_params.conn_icid = (u16)qedi_conn->iscsi_conn_id;
	task_params.itid = tid;
	task_params.cq_rss_number = cq_idx;
	if (task_type == ISCSI_TASK_TYPE_INITIATOR_WRITE)
		task_params.tx_io_size = scsi_bufflen(sc);
	else if (task_type == ISCSI_TASK_TYPE_INITIATOR_READ)
		task_params.rx_io_size = scsi_bufflen(sc);

	sq_idx = qedi_get_wqe_idx(qedi_conn);
	task_params.sqe = &ep->sq[sq_idx];

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_IO,
		  "%s: %s-SGL: sg_len=0x%x num_sges=0x%x first-sge-lo=0x%x first-sge-hi=0x%x\n",
		  (task_type == ISCSI_TASK_TYPE_INITIATOR_WRITE) ?
		  "Write " : "Read ", (cmd->io_tbl.sge_valid == 1) ?
		  "Single" : (cmd->use_slowpath ? "SLOW" : "FAST"),
		  (u16)cmd->io_tbl.sge_valid, scsi_bufflen(sc),
		  (u32)(cmd->io_tbl.sge_tbl_dma),
		  (u32)((u64)cmd->io_tbl.sge_tbl_dma >> 32));

	memset(task_params.sqe, 0, sizeof(struct iscsi_wqe));

	if (task_params.tx_io_size != 0)
		ptx_sgl = &tx_sgl_task_params;
	if (task_params.rx_io_size != 0)
		prx_sgl = &rx_sgl_task_params;

	rval = init_initiator_rw_iscsi_task(&task_params, &conn_params,
					    &cmd_params, &cmd_pdu_header,
					    ptx_sgl, prx_sgl,
					    NULL);
	if (rval)
		return -1;

	spin_lock(&qedi_conn->list_lock);
	list_add_tail(&cmd->io_cmd, &qedi_conn->active_cmd_list);
	cmd->io_cmd_in_list = true;
	qedi_conn->active_cmd_count++;
	spin_unlock(&qedi_conn->list_lock);

	qedi_ring_doorbell(qedi_conn);
	return 0;
}