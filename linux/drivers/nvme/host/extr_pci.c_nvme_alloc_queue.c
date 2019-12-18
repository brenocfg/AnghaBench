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
struct nvme_queue {int q_depth; int cq_phase; int qid; int /*<<< orphan*/  cq_dma_addr; scalar_t__ cqes; int /*<<< orphan*/ * q_db; scalar_t__ cq_head; int /*<<< orphan*/  cq_poll_lock; int /*<<< orphan*/  sq_lock; struct nvme_dev* dev; int /*<<< orphan*/  sqes; } ;
struct TYPE_2__ {int queue_count; } ;
struct nvme_dev {int db_stride; int /*<<< orphan*/  dev; TYPE_1__ ctrl; int /*<<< orphan*/ * dbs; int /*<<< orphan*/  io_sqes; struct nvme_queue* queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQ_SIZE (struct nvme_queue*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVME_ADM_SQES ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ nvme_alloc_sq_cmds (struct nvme_dev*,struct nvme_queue*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvme_alloc_queue(struct nvme_dev *dev, int qid, int depth)
{
	struct nvme_queue *nvmeq = &dev->queues[qid];

	if (dev->ctrl.queue_count > qid)
		return 0;

	nvmeq->sqes = qid ? dev->io_sqes : NVME_ADM_SQES;
	nvmeq->q_depth = depth;
	nvmeq->cqes = dma_alloc_coherent(dev->dev, CQ_SIZE(nvmeq),
					 &nvmeq->cq_dma_addr, GFP_KERNEL);
	if (!nvmeq->cqes)
		goto free_nvmeq;

	if (nvme_alloc_sq_cmds(dev, nvmeq, qid))
		goto free_cqdma;

	nvmeq->dev = dev;
	spin_lock_init(&nvmeq->sq_lock);
	spin_lock_init(&nvmeq->cq_poll_lock);
	nvmeq->cq_head = 0;
	nvmeq->cq_phase = 1;
	nvmeq->q_db = &dev->dbs[qid * 2 * dev->db_stride];
	nvmeq->qid = qid;
	dev->ctrl.queue_count++;

	return 0;

 free_cqdma:
	dma_free_coherent(dev->dev, CQ_SIZE(nvmeq), (void *)nvmeq->cqes,
			  nvmeq->cq_dma_addr);
 free_nvmeq:
	return -ENOMEM;
}