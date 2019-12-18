#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  size_t uint32_t ;
typedef  scalar_t__ uint16_t ;
struct scsi_qla_host {scalar_t__ marker_needed; int /*<<< orphan*/  vp_idx; struct qla_hw_data* hw; } ;
struct scsi_cmnd {unsigned char* host_scribble; int /*<<< orphan*/  cmd_len; int /*<<< orphan*/  cmnd; TYPE_5__* device; int /*<<< orphan*/  sc_data_direction; } ;
struct req_que {scalar_t__ cnt; scalar_t__* out_ptr; scalar_t__ ring_index; scalar_t__ length; size_t current_outstanding_cmd; int /*<<< orphan*/  req_q_in; scalar_t__ ring_ptr; scalar_t__ ring; int /*<<< orphan*/  id; TYPE_6__** outstanding_cmds; int /*<<< orphan*/  req_q_out; } ;
struct qla_qpair {int /*<<< orphan*/  qp_lock; struct req_que* req; } ;
struct qla_hw_data {TYPE_1__* pdev; } ;
struct cmd_type_7 {scalar_t__ entry_count; int /*<<< orphan*/  byte_count; scalar_t__* fcp_cdb; int /*<<< orphan*/  task; int /*<<< orphan*/  lun; int /*<<< orphan*/  vp_index; int /*<<< orphan*/ * port_id; void* nport_handle; void* dseg_count; int /*<<< orphan*/  handle; } ;
struct TYPE_15__ {size_t handle; int /*<<< orphan*/  flags; TYPE_4__* fcport; struct qla_qpair* qpair; } ;
typedef  TYPE_6__ srb_t ;
struct TYPE_14__ {int /*<<< orphan*/  lun; } ;
struct TYPE_11__ {int /*<<< orphan*/  domain; int /*<<< orphan*/  area; int /*<<< orphan*/  al_pa; } ;
struct TYPE_12__ {TYPE_2__ b; } ;
struct TYPE_13__ {scalar_t__ loop_id; struct scsi_qla_host* vha; TYPE_3__ d_id; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct scsi_cmnd* GET_CMD_SP (TYPE_6__*) ; 
 scalar_t__ IS_SHADOW_REG_CAPABLE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  MAKE_HANDLE (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  MK_SYNC_ALL ; 
 int QLA_FUNCTION_FAILED ; 
 scalar_t__ QLA_SUCCESS ; 
 scalar_t__ RD_REG_DWORD_RELAXED (int /*<<< orphan*/ ) ; 
 scalar_t__ REQUEST_ENTRY_SIZE ; 
 int /*<<< orphan*/  SRB_DMA_VALID ; 
 int /*<<< orphan*/  TSK_SIMPLE ; 
 int /*<<< orphan*/  WRT_REG_DWORD (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ __qla2x00_marker (struct scsi_qla_host*,struct qla_qpair*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (size_t) ; 
 int dma_map_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_to_fcp_swap (scalar_t__*,int) ; 
 int /*<<< orphan*/  int_to_scsilun (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  qla24xx_build_scsi_iocbs (TYPE_6__*,struct cmd_type_7*,scalar_t__,struct req_que*) ; 
 scalar_t__ qla24xx_calc_iocbs (struct scsi_qla_host*,scalar_t__) ; 
 size_t qla2xxx_get_next_handle (struct req_que*) ; 
 scalar_t__ scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 scalar_t__ scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int
qla2xxx_start_scsi_mq(srb_t *sp)
{
	int		nseg;
	unsigned long   flags;
	uint32_t	*clr_ptr;
	uint32_t	handle;
	struct cmd_type_7 *cmd_pkt;
	uint16_t	cnt;
	uint16_t	req_cnt;
	uint16_t	tot_dsds;
	struct req_que *req = NULL;
	struct scsi_cmnd *cmd = GET_CMD_SP(sp);
	struct scsi_qla_host *vha = sp->fcport->vha;
	struct qla_hw_data *ha = vha->hw;
	struct qla_qpair *qpair = sp->qpair;

	/* Acquire qpair specific lock */
	spin_lock_irqsave(&qpair->qp_lock, flags);

	/* Setup qpair pointers */
	req = qpair->req;

	/* So we know we haven't pci_map'ed anything yet */
	tot_dsds = 0;

	/* Send marker if required */
	if (vha->marker_needed != 0) {
		if (__qla2x00_marker(vha, qpair, 0, 0, MK_SYNC_ALL) !=
		    QLA_SUCCESS) {
			spin_unlock_irqrestore(&qpair->qp_lock, flags);
			return QLA_FUNCTION_FAILED;
		}
		vha->marker_needed = 0;
	}

	handle = qla2xxx_get_next_handle(req);
	if (handle == 0)
		goto queuing_error;

	/* Map the sg table so we have an accurate count of sg entries needed */
	if (scsi_sg_count(cmd)) {
		nseg = dma_map_sg(&ha->pdev->dev, scsi_sglist(cmd),
		    scsi_sg_count(cmd), cmd->sc_data_direction);
		if (unlikely(!nseg))
			goto queuing_error;
	} else
		nseg = 0;

	tot_dsds = nseg;
	req_cnt = qla24xx_calc_iocbs(vha, tot_dsds);
	if (req->cnt < (req_cnt + 2)) {
		cnt = IS_SHADOW_REG_CAPABLE(ha) ? *req->out_ptr :
		    RD_REG_DWORD_RELAXED(req->req_q_out);
		if (req->ring_index < cnt)
			req->cnt = cnt - req->ring_index;
		else
			req->cnt = req->length -
				(req->ring_index - cnt);
		if (req->cnt < (req_cnt + 2))
			goto queuing_error;
	}

	/* Build command packet. */
	req->current_outstanding_cmd = handle;
	req->outstanding_cmds[handle] = sp;
	sp->handle = handle;
	cmd->host_scribble = (unsigned char *)(unsigned long)handle;
	req->cnt -= req_cnt;

	cmd_pkt = (struct cmd_type_7 *)req->ring_ptr;
	cmd_pkt->handle = MAKE_HANDLE(req->id, handle);

	/* Zero out remaining portion of packet. */
	/*    tagged queuing modifier -- default is TSK_SIMPLE (0). */
	clr_ptr = (uint32_t *)cmd_pkt + 2;
	memset(clr_ptr, 0, REQUEST_ENTRY_SIZE - 8);
	cmd_pkt->dseg_count = cpu_to_le16(tot_dsds);

	/* Set NPORT-ID and LUN number*/
	cmd_pkt->nport_handle = cpu_to_le16(sp->fcport->loop_id);
	cmd_pkt->port_id[0] = sp->fcport->d_id.b.al_pa;
	cmd_pkt->port_id[1] = sp->fcport->d_id.b.area;
	cmd_pkt->port_id[2] = sp->fcport->d_id.b.domain;
	cmd_pkt->vp_index = sp->fcport->vha->vp_idx;

	int_to_scsilun(cmd->device->lun, &cmd_pkt->lun);
	host_to_fcp_swap((uint8_t *)&cmd_pkt->lun, sizeof(cmd_pkt->lun));

	cmd_pkt->task = TSK_SIMPLE;

	/* Load SCSI command packet. */
	memcpy(cmd_pkt->fcp_cdb, cmd->cmnd, cmd->cmd_len);
	host_to_fcp_swap(cmd_pkt->fcp_cdb, sizeof(cmd_pkt->fcp_cdb));

	cmd_pkt->byte_count = cpu_to_le32((uint32_t)scsi_bufflen(cmd));

	/* Build IOCB segments */
	qla24xx_build_scsi_iocbs(sp, cmd_pkt, tot_dsds, req);

	/* Set total data segment count. */
	cmd_pkt->entry_count = (uint8_t)req_cnt;
	wmb();
	/* Adjust ring index. */
	req->ring_index++;
	if (req->ring_index == req->length) {
		req->ring_index = 0;
		req->ring_ptr = req->ring;
	} else
		req->ring_ptr++;

	sp->flags |= SRB_DMA_VALID;

	/* Set chip new ring index. */
	WRT_REG_DWORD(req->req_q_in, req->ring_index);

	spin_unlock_irqrestore(&qpair->qp_lock, flags);
	return QLA_SUCCESS;

queuing_error:
	if (tot_dsds)
		scsi_dma_unmap(cmd);

	spin_unlock_irqrestore(&qpair->qp_lock, flags);

	return QLA_FUNCTION_FAILED;
}