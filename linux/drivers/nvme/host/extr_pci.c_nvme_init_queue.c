#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u16 ;
struct nvme_queue {int cq_phase; scalar_t__ cqes; int /*<<< orphan*/ * q_db; scalar_t__ cq_head; scalar_t__ last_sq_tail; scalar_t__ sq_tail; struct nvme_dev* dev; } ;
struct nvme_dev {int db_stride; int /*<<< orphan*/  online_queues; int /*<<< orphan*/ * dbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQ_SIZE (struct nvme_queue*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_dbbuf_init (struct nvme_dev*,struct nvme_queue*,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void nvme_init_queue(struct nvme_queue *nvmeq, u16 qid)
{
	struct nvme_dev *dev = nvmeq->dev;

	nvmeq->sq_tail = 0;
	nvmeq->last_sq_tail = 0;
	nvmeq->cq_head = 0;
	nvmeq->cq_phase = 1;
	nvmeq->q_db = &dev->dbs[qid * 2 * dev->db_stride];
	memset((void *)nvmeq->cqes, 0, CQ_SIZE(nvmeq));
	nvme_dbbuf_init(dev, nvmeq, qid);
	dev->online_queues++;
	wmb(); /* ensure the first interrupt sees the initialization */
}