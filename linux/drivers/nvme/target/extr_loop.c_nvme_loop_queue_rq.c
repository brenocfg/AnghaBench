#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct request {int /*<<< orphan*/  q; } ;
struct nvme_ns {int dummy; } ;
struct nvme_loop_queue {int /*<<< orphan*/  nvme_sq; int /*<<< orphan*/  nvme_cq; TYPE_3__* ctrl; int /*<<< orphan*/  flags; } ;
struct TYPE_11__ {int /*<<< orphan*/  transfer_len; int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg; int /*<<< orphan*/  port; } ;
struct TYPE_10__ {int /*<<< orphan*/  sgl; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
struct TYPE_12__ {TYPE_2__ common; } ;
struct nvme_loop_iod {int /*<<< orphan*/  work; TYPE_5__ req; TYPE_4__ sg_table; int /*<<< orphan*/  first_sgl; TYPE_6__ cmd; } ;
struct blk_mq_queue_data {struct request* rq; } ;
struct blk_mq_hw_ctx {struct nvme_loop_queue* driver_data; TYPE_1__* queue; } ;
typedef  scalar_t__ blk_status_t ;
struct TYPE_9__ {int /*<<< orphan*/  port; int /*<<< orphan*/  ctrl; } ;
struct TYPE_7__ {struct nvme_ns* queuedata; } ;

/* Variables and functions */
 scalar_t__ BLK_STS_OK ; 
 scalar_t__ BLK_STS_RESOURCE ; 
 int /*<<< orphan*/  NVME_CMD_SGL_METABUF ; 
 int /*<<< orphan*/  NVME_LOOP_Q_LIVE ; 
 int /*<<< orphan*/  SG_CHUNK_SIZE ; 
 struct nvme_loop_iod* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  blk_mq_start_request (struct request*) ; 
 int /*<<< orphan*/  blk_rq_map_sg (int /*<<< orphan*/ ,struct request*,int /*<<< orphan*/ ) ; 
 scalar_t__ blk_rq_nr_phys_segments (struct request*) ; 
 int /*<<< orphan*/  blk_rq_payload_bytes (struct request*) ; 
 int /*<<< orphan*/  nvme_cleanup_cmd (struct request*) ; 
 int /*<<< orphan*/  nvme_loop_ops ; 
 scalar_t__ nvme_setup_cmd (struct nvme_ns*,struct request*,TYPE_6__*) ; 
 int /*<<< orphan*/  nvmet_req_init (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmf_check_ready (int /*<<< orphan*/ *,struct request*,int) ; 
 scalar_t__ nvmf_fail_nonready_command (int /*<<< orphan*/ *,struct request*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ sg_alloc_table_chained (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static blk_status_t nvme_loop_queue_rq(struct blk_mq_hw_ctx *hctx,
		const struct blk_mq_queue_data *bd)
{
	struct nvme_ns *ns = hctx->queue->queuedata;
	struct nvme_loop_queue *queue = hctx->driver_data;
	struct request *req = bd->rq;
	struct nvme_loop_iod *iod = blk_mq_rq_to_pdu(req);
	bool queue_ready = test_bit(NVME_LOOP_Q_LIVE, &queue->flags);
	blk_status_t ret;

	if (!nvmf_check_ready(&queue->ctrl->ctrl, req, queue_ready))
		return nvmf_fail_nonready_command(&queue->ctrl->ctrl, req);

	ret = nvme_setup_cmd(ns, req, &iod->cmd);
	if (ret)
		return ret;

	blk_mq_start_request(req);
	iod->cmd.common.flags |= NVME_CMD_SGL_METABUF;
	iod->req.port = queue->ctrl->port;
	if (!nvmet_req_init(&iod->req, &queue->nvme_cq,
			&queue->nvme_sq, &nvme_loop_ops))
		return BLK_STS_OK;

	if (blk_rq_nr_phys_segments(req)) {
		iod->sg_table.sgl = iod->first_sgl;
		if (sg_alloc_table_chained(&iod->sg_table,
				blk_rq_nr_phys_segments(req),
				iod->sg_table.sgl, SG_CHUNK_SIZE)) {
			nvme_cleanup_cmd(req);
			return BLK_STS_RESOURCE;
		}

		iod->req.sg = iod->sg_table.sgl;
		iod->req.sg_cnt = blk_rq_map_sg(req->q, req, iod->sg_table.sgl);
		iod->req.transfer_len = blk_rq_payload_bytes(req);
	}

	schedule_work(&iod->work);
	return BLK_STS_OK;
}