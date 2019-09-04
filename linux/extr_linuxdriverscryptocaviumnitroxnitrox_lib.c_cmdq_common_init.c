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
typedef  int u32 ;
struct nitrox_device {int qlen; } ;
struct nitrox_cmdq {int instr_size; int /*<<< orphan*/  backlog_count; int /*<<< orphan*/  pending_count; int /*<<< orphan*/  backlog_qflush; int /*<<< orphan*/  backlog_head; int /*<<< orphan*/  response_head; int /*<<< orphan*/  backlog_lock; int /*<<< orphan*/  cmdq_lock; int /*<<< orphan*/  response_lock; scalar_t__ write_idx; scalar_t__ qsize; int /*<<< orphan*/  dma_unaligned; void* dma; int /*<<< orphan*/  head_unaligned; void* head; struct nitrox_device* ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV (struct nitrox_device*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PKT_IN_ALIGN ; 
 void* PTR_ALIGN (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  backlog_qflush_work ; 
 int /*<<< orphan*/  dma_zalloc_coherent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmdq_common_init(struct nitrox_cmdq *cmdq)
{
	struct nitrox_device *ndev = cmdq->ndev;
	u32 qsize;

	qsize = (ndev->qlen) * cmdq->instr_size;
	cmdq->head_unaligned = dma_zalloc_coherent(DEV(ndev),
						   (qsize + PKT_IN_ALIGN),
						   &cmdq->dma_unaligned,
						   GFP_KERNEL);
	if (!cmdq->head_unaligned)
		return -ENOMEM;

	cmdq->head = PTR_ALIGN(cmdq->head_unaligned, PKT_IN_ALIGN);
	cmdq->dma = PTR_ALIGN(cmdq->dma_unaligned, PKT_IN_ALIGN);
	cmdq->qsize = (qsize + PKT_IN_ALIGN);
	cmdq->write_idx = 0;

	spin_lock_init(&cmdq->response_lock);
	spin_lock_init(&cmdq->cmdq_lock);
	spin_lock_init(&cmdq->backlog_lock);

	INIT_LIST_HEAD(&cmdq->response_head);
	INIT_LIST_HEAD(&cmdq->backlog_head);
	INIT_WORK(&cmdq->backlog_qflush, backlog_qflush_work);

	atomic_set(&cmdq->pending_count, 0);
	atomic_set(&cmdq->backlog_count, 0);
	return 0;
}