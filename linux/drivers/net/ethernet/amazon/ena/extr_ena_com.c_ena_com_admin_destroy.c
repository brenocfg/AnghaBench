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
typedef  int /*<<< orphan*/  u16 ;
struct ena_com_aenq {int /*<<< orphan*/ * entries; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  q_depth; } ;
struct ena_com_admin_sq {int /*<<< orphan*/ * entries; int /*<<< orphan*/  dma_addr; } ;
struct ena_com_admin_cq {int /*<<< orphan*/ * entries; int /*<<< orphan*/  dma_addr; } ;
struct ena_com_admin_queue {int /*<<< orphan*/  q_depth; int /*<<< orphan*/ * comp_ctx; struct ena_com_admin_sq sq; struct ena_com_admin_cq cq; } ;
struct ena_com_dev {int /*<<< orphan*/  dmadev; struct ena_com_aenq aenq; struct ena_com_admin_queue admin_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADMIN_AENQ_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADMIN_CQ_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADMIN_SQ_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ena_com_admin_destroy(struct ena_com_dev *ena_dev)
{
	struct ena_com_admin_queue *admin_queue = &ena_dev->admin_queue;
	struct ena_com_admin_cq *cq = &admin_queue->cq;
	struct ena_com_admin_sq *sq = &admin_queue->sq;
	struct ena_com_aenq *aenq = &ena_dev->aenq;
	u16 size;

	if (admin_queue->comp_ctx)
		devm_kfree(ena_dev->dmadev, admin_queue->comp_ctx);
	admin_queue->comp_ctx = NULL;
	size = ADMIN_SQ_SIZE(admin_queue->q_depth);
	if (sq->entries)
		dma_free_coherent(ena_dev->dmadev, size, sq->entries,
				  sq->dma_addr);
	sq->entries = NULL;

	size = ADMIN_CQ_SIZE(admin_queue->q_depth);
	if (cq->entries)
		dma_free_coherent(ena_dev->dmadev, size, cq->entries,
				  cq->dma_addr);
	cq->entries = NULL;

	size = ADMIN_AENQ_SIZE(aenq->q_depth);
	if (ena_dev->aenq.entries)
		dma_free_coherent(ena_dev->dmadev, size, aenq->entries,
				  aenq->dma_addr);
	aenq->entries = NULL;
}