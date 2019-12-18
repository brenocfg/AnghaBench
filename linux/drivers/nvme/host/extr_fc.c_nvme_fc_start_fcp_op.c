#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nvme_fc_queue {int /*<<< orphan*/  lldd_handle; int /*<<< orphan*/  csn; int /*<<< orphan*/  qnum; int /*<<< orphan*/  connection_id; } ;
struct TYPE_18__ {int io_dir; int /*<<< orphan*/  cmddma; int /*<<< orphan*/  sqid; int /*<<< orphan*/  status; scalar_t__ rcv_rsplen; scalar_t__ transferred_length; int /*<<< orphan*/  payload_length; } ;
struct TYPE_11__ {int type; scalar_t__ addr; int /*<<< orphan*/  length; } ;
struct TYPE_12__ {TYPE_2__ sgl; } ;
struct TYPE_13__ {TYPE_3__ dptr; } ;
struct TYPE_10__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  metadata; } ;
struct nvme_command {TYPE_4__ rw; TYPE_1__ common; } ;
struct nvme_fc_cmd_iu {void* csn; int /*<<< orphan*/  flags; void* data_len; int /*<<< orphan*/  connection_id; struct nvme_command sqe; } ;
struct nvme_fc_fcp_op {int flags; int /*<<< orphan*/  rq; int /*<<< orphan*/  state; TYPE_9__ fcp_req; struct nvme_fc_cmd_iu cmd_iu; } ;
struct nvme_fc_ctrl {TYPE_7__* rport; TYPE_6__* lport; } ;
typedef  enum nvmefc_fcp_datadir { ____Placeholder_nvmefc_fcp_datadir } nvmefc_fcp_datadir ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_17__ {scalar_t__ port_state; } ;
struct TYPE_16__ {TYPE_8__ remoteport; } ;
struct TYPE_15__ {int /*<<< orphan*/  localport; TYPE_5__* ops; int /*<<< orphan*/  dev; } ;
struct TYPE_14__ {int (* fcp_io ) (int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ ,TYPE_9__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EAGAIN ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FCNVME_CMD_FLAGS_READ ; 
 int /*<<< orphan*/  FCNVME_CMD_FLAGS_WRITE ; 
 int FCOP_FLAGS_AEN ; 
 int /*<<< orphan*/  FCPOP_STATE_ACTIVE ; 
 int /*<<< orphan*/  FCPOP_STATE_COMPLETE ; 
 scalar_t__ FC_OBJSTATE_ONLINE ; 
#define  NVMEFC_FCP_NODATA 130 
#define  NVMEFC_FCP_READ 129 
#define  NVMEFC_FCP_WRITE 128 
 int /*<<< orphan*/  NVME_CMD_SGL_METABUF ; 
 int /*<<< orphan*/  NVME_SC_SUCCESS ; 
 int NVME_SGL_FMT_TRANSPORT_A ; 
 int NVME_TRANSPORT_SGL_DATA_DESC ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __nvme_fc_fcpop_chk_teardowns (struct nvme_fc_ctrl*,struct nvme_fc_fcp_op*,int) ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_start_request (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_cleanup_cmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_fc_ctrl_get (struct nvme_fc_ctrl*) ; 
 int /*<<< orphan*/  nvme_fc_ctrl_put (struct nvme_fc_ctrl*) ; 
 int nvme_fc_map_data (struct nvme_fc_ctrl*,int /*<<< orphan*/ ,struct nvme_fc_fcp_op*) ; 
 int /*<<< orphan*/  nvme_fc_unmap_data (struct nvme_fc_ctrl*,int /*<<< orphan*/ ,struct nvme_fc_fcp_op*) ; 
 int stub1 (int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ ,TYPE_9__*) ; 

__attribute__((used)) static blk_status_t
nvme_fc_start_fcp_op(struct nvme_fc_ctrl *ctrl, struct nvme_fc_queue *queue,
	struct nvme_fc_fcp_op *op, u32 data_len,
	enum nvmefc_fcp_datadir	io_dir)
{
	struct nvme_fc_cmd_iu *cmdiu = &op->cmd_iu;
	struct nvme_command *sqe = &cmdiu->sqe;
	int ret, opstate;

	/*
	 * before attempting to send the io, check to see if we believe
	 * the target device is present
	 */
	if (ctrl->rport->remoteport.port_state != FC_OBJSTATE_ONLINE)
		return BLK_STS_RESOURCE;

	if (!nvme_fc_ctrl_get(ctrl))
		return BLK_STS_IOERR;

	/* format the FC-NVME CMD IU and fcp_req */
	cmdiu->connection_id = cpu_to_be64(queue->connection_id);
	cmdiu->data_len = cpu_to_be32(data_len);
	switch (io_dir) {
	case NVMEFC_FCP_WRITE:
		cmdiu->flags = FCNVME_CMD_FLAGS_WRITE;
		break;
	case NVMEFC_FCP_READ:
		cmdiu->flags = FCNVME_CMD_FLAGS_READ;
		break;
	case NVMEFC_FCP_NODATA:
		cmdiu->flags = 0;
		break;
	}
	op->fcp_req.payload_length = data_len;
	op->fcp_req.io_dir = io_dir;
	op->fcp_req.transferred_length = 0;
	op->fcp_req.rcv_rsplen = 0;
	op->fcp_req.status = NVME_SC_SUCCESS;
	op->fcp_req.sqid = cpu_to_le16(queue->qnum);

	/*
	 * validate per fabric rules, set fields mandated by fabric spec
	 * as well as those by FC-NVME spec.
	 */
	WARN_ON_ONCE(sqe->common.metadata);
	sqe->common.flags |= NVME_CMD_SGL_METABUF;

	/*
	 * format SQE DPTR field per FC-NVME rules:
	 *    type=0x5     Transport SGL Data Block Descriptor
	 *    subtype=0xA  Transport-specific value
	 *    address=0
	 *    length=length of the data series
	 */
	sqe->rw.dptr.sgl.type = (NVME_TRANSPORT_SGL_DATA_DESC << 4) |
					NVME_SGL_FMT_TRANSPORT_A;
	sqe->rw.dptr.sgl.length = cpu_to_le32(data_len);
	sqe->rw.dptr.sgl.addr = 0;

	if (!(op->flags & FCOP_FLAGS_AEN)) {
		ret = nvme_fc_map_data(ctrl, op->rq, op);
		if (ret < 0) {
			nvme_cleanup_cmd(op->rq);
			nvme_fc_ctrl_put(ctrl);
			if (ret == -ENOMEM || ret == -EAGAIN)
				return BLK_STS_RESOURCE;
			return BLK_STS_IOERR;
		}
	}

	fc_dma_sync_single_for_device(ctrl->lport->dev, op->fcp_req.cmddma,
				  sizeof(op->cmd_iu), DMA_TO_DEVICE);

	atomic_set(&op->state, FCPOP_STATE_ACTIVE);

	if (!(op->flags & FCOP_FLAGS_AEN))
		blk_mq_start_request(op->rq);

	cmdiu->csn = cpu_to_be32(atomic_inc_return(&queue->csn));
	ret = ctrl->lport->ops->fcp_io(&ctrl->lport->localport,
					&ctrl->rport->remoteport,
					queue->lldd_handle, &op->fcp_req);

	if (ret) {
		/*
		 * If the lld fails to send the command is there an issue with
		 * the csn value?  If the command that fails is the Connect,
		 * no - as the connection won't be live.  If it is a command
		 * post-connect, it's possible a gap in csn may be created.
		 * Does this matter?  As Linux initiators don't send fused
		 * commands, no.  The gap would exist, but as there's nothing
		 * that depends on csn order to be delivered on the target
		 * side, it shouldn't hurt.  It would be difficult for a
		 * target to even detect the csn gap as it has no idea when the
		 * cmd with the csn was supposed to arrive.
		 */
		opstate = atomic_xchg(&op->state, FCPOP_STATE_COMPLETE);
		__nvme_fc_fcpop_chk_teardowns(ctrl, op, opstate);

		if (!(op->flags & FCOP_FLAGS_AEN))
			nvme_fc_unmap_data(ctrl, op->rq, op);

		nvme_fc_ctrl_put(ctrl);

		if (ctrl->rport->remoteport.port_state == FC_OBJSTATE_ONLINE &&
				ret != -EBUSY)
			return BLK_STS_IOERR;

		return BLK_STS_RESOURCE;
	}

	return BLK_STS_OK;
}