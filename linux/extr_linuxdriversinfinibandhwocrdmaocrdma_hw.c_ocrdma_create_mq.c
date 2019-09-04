#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct ocrdma_mqe {int dummy; } ;
struct ocrdma_mcqe {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  id; } ;
struct TYPE_11__ {TYPE_3__ cq; TYPE_3__ sq; } ;
struct TYPE_13__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cmd_wait; } ;
struct ocrdma_dev {TYPE_2__ mq; TYPE_9__ mqe_ctx; TYPE_1__* eq_tbl; } ;
struct TYPE_10__ {int /*<<< orphan*/  q; int /*<<< orphan*/  cq_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCRDMA_MQ_CQ_LEN ; 
 int /*<<< orphan*/  OCRDMA_MQ_LEN ; 
 int /*<<< orphan*/  QTYPE_CQ ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int ocrdma_alloc_q (struct ocrdma_dev*,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocrdma_free_q (struct ocrdma_dev*,TYPE_3__*) ; 
 int ocrdma_mbx_create_mq (struct ocrdma_dev*,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ocrdma_mbx_delete_q (struct ocrdma_dev*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ocrdma_mbx_mq_cq_create (struct ocrdma_dev*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocrdma_ring_cq_db (struct ocrdma_dev*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocrdma_create_mq(struct ocrdma_dev *dev)
{
	int status;

	/* Alloc completion queue for Mailbox queue */
	status = ocrdma_alloc_q(dev, &dev->mq.cq, OCRDMA_MQ_CQ_LEN,
				sizeof(struct ocrdma_mcqe));
	if (status)
		goto alloc_err;

	dev->eq_tbl[0].cq_cnt++;
	status = ocrdma_mbx_mq_cq_create(dev, &dev->mq.cq, &dev->eq_tbl[0].q);
	if (status)
		goto mbx_cq_free;

	memset(&dev->mqe_ctx, 0, sizeof(dev->mqe_ctx));
	init_waitqueue_head(&dev->mqe_ctx.cmd_wait);
	mutex_init(&dev->mqe_ctx.lock);

	/* Alloc Mailbox queue */
	status = ocrdma_alloc_q(dev, &dev->mq.sq, OCRDMA_MQ_LEN,
				sizeof(struct ocrdma_mqe));
	if (status)
		goto mbx_cq_destroy;
	status = ocrdma_mbx_create_mq(dev, &dev->mq.sq, &dev->mq.cq);
	if (status)
		goto mbx_q_free;
	ocrdma_ring_cq_db(dev, dev->mq.cq.id, true, false, 0);
	return 0;

mbx_q_free:
	ocrdma_free_q(dev, &dev->mq.sq);
mbx_cq_destroy:
	ocrdma_mbx_delete_q(dev, &dev->mq.cq, QTYPE_CQ);
mbx_cq_free:
	ocrdma_free_q(dev, &dev->mq.cq);
alloc_err:
	return status;
}