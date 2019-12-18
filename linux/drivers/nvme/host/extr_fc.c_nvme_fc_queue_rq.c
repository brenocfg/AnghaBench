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
typedef  scalar_t__ u32 ;
struct request {int dummy; } ;
struct nvme_ns {int dummy; } ;
struct nvme_fc_queue {struct nvme_fc_ctrl* ctrl; int /*<<< orphan*/  flags; } ;
struct nvme_command {int dummy; } ;
struct nvme_fc_cmd_iu {struct nvme_command sqe; } ;
struct nvme_fc_fcp_op {struct nvme_fc_cmd_iu cmd_iu; } ;
struct nvme_fc_ctrl {int /*<<< orphan*/  ctrl; TYPE_3__* rport; } ;
struct blk_mq_queue_data {struct request* rq; } ;
struct blk_mq_hw_ctx {struct nvme_fc_queue* driver_data; TYPE_1__* queue; } ;
typedef  enum nvmefc_fcp_datadir { ____Placeholder_nvmefc_fcp_datadir } nvmefc_fcp_datadir ;
typedef  scalar_t__ blk_status_t ;
struct TYPE_5__ {scalar_t__ port_state; } ;
struct TYPE_6__ {TYPE_2__ remoteport; } ;
struct TYPE_4__ {struct nvme_ns* queuedata; } ;

/* Variables and functions */
 scalar_t__ FC_OBJSTATE_ONLINE ; 
 int NVMEFC_FCP_NODATA ; 
 int NVMEFC_FCP_READ ; 
 int NVMEFC_FCP_WRITE ; 
 int /*<<< orphan*/  NVME_FC_Q_LIVE ; 
 scalar_t__ WRITE ; 
 struct nvme_fc_fcp_op* blk_mq_rq_to_pdu (struct request*) ; 
 scalar_t__ blk_rq_nr_phys_segments (struct request*) ; 
 scalar_t__ blk_rq_payload_bytes (struct request*) ; 
 scalar_t__ nvme_fc_start_fcp_op (struct nvme_fc_ctrl*,struct nvme_fc_queue*,struct nvme_fc_fcp_op*,scalar_t__,int) ; 
 scalar_t__ nvme_setup_cmd (struct nvme_ns*,struct request*,struct nvme_command*) ; 
 int /*<<< orphan*/  nvmf_check_ready (int /*<<< orphan*/ *,struct request*,int) ; 
 scalar_t__ nvmf_fail_nonready_command (int /*<<< orphan*/ *,struct request*) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static blk_status_t
nvme_fc_queue_rq(struct blk_mq_hw_ctx *hctx,
			const struct blk_mq_queue_data *bd)
{
	struct nvme_ns *ns = hctx->queue->queuedata;
	struct nvme_fc_queue *queue = hctx->driver_data;
	struct nvme_fc_ctrl *ctrl = queue->ctrl;
	struct request *rq = bd->rq;
	struct nvme_fc_fcp_op *op = blk_mq_rq_to_pdu(rq);
	struct nvme_fc_cmd_iu *cmdiu = &op->cmd_iu;
	struct nvme_command *sqe = &cmdiu->sqe;
	enum nvmefc_fcp_datadir	io_dir;
	bool queue_ready = test_bit(NVME_FC_Q_LIVE, &queue->flags);
	u32 data_len;
	blk_status_t ret;

	if (ctrl->rport->remoteport.port_state != FC_OBJSTATE_ONLINE ||
	    !nvmf_check_ready(&queue->ctrl->ctrl, rq, queue_ready))
		return nvmf_fail_nonready_command(&queue->ctrl->ctrl, rq);

	ret = nvme_setup_cmd(ns, rq, sqe);
	if (ret)
		return ret;

	/*
	 * nvme core doesn't quite treat the rq opaquely. Commands such
	 * as WRITE ZEROES will return a non-zero rq payload_bytes yet
	 * there is no actual payload to be transferred.
	 * To get it right, key data transmission on there being 1 or
	 * more physical segments in the sg list. If there is no
	 * physical segments, there is no payload.
	 */
	if (blk_rq_nr_phys_segments(rq)) {
		data_len = blk_rq_payload_bytes(rq);
		io_dir = ((rq_data_dir(rq) == WRITE) ?
					NVMEFC_FCP_WRITE : NVMEFC_FCP_READ);
	} else {
		data_len = 0;
		io_dir = NVMEFC_FCP_NODATA;
	}


	return nvme_fc_start_fcp_op(ctrl, queue, op, data_len, io_dir);
}