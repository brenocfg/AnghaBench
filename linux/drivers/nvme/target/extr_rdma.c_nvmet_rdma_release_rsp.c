#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ sg; int /*<<< orphan*/  sg_cnt; } ;
struct nvmet_rdma_rsp {TYPE_3__ req; TYPE_2__* cmd; int /*<<< orphan*/  rw; scalar_t__ n_rdma; struct nvmet_rdma_queue* queue; } ;
struct nvmet_rdma_queue {int /*<<< orphan*/  rsp_wr_wait_list; TYPE_1__* cm_id; int /*<<< orphan*/  sq_wr_avail; } ;
struct TYPE_6__ {scalar_t__ inline_sg; } ;
struct TYPE_5__ {int /*<<< orphan*/  port_num; int /*<<< orphan*/  qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty_careful (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_data_dir (TYPE_3__*) ; 
 int /*<<< orphan*/  nvmet_rdma_process_wr_wait_list (struct nvmet_rdma_queue*) ; 
 int /*<<< orphan*/  nvmet_rdma_put_rsp (struct nvmet_rdma_rsp*) ; 
 int /*<<< orphan*/  nvmet_req_free_sgl (TYPE_3__*) ; 
 int /*<<< orphan*/  rdma_rw_ctx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void nvmet_rdma_release_rsp(struct nvmet_rdma_rsp *rsp)
{
	struct nvmet_rdma_queue *queue = rsp->queue;

	atomic_add(1 + rsp->n_rdma, &queue->sq_wr_avail);

	if (rsp->n_rdma) {
		rdma_rw_ctx_destroy(&rsp->rw, queue->cm_id->qp,
				queue->cm_id->port_num, rsp->req.sg,
				rsp->req.sg_cnt, nvmet_data_dir(&rsp->req));
	}

	if (rsp->req.sg != rsp->cmd->inline_sg)
		nvmet_req_free_sgl(&rsp->req);

	if (unlikely(!list_empty_careful(&queue->rsp_wr_wait_list)))
		nvmet_rdma_process_wr_wait_list(queue);

	nvmet_rdma_put_rsp(rsp);
}