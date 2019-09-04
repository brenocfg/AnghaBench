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
struct nitrox_device {int dummy; } ;
struct nitrox_cmdq {scalar_t__ instr_size; int /*<<< orphan*/  qsize; scalar_t__ dma; int /*<<< orphan*/ * head; int /*<<< orphan*/ * dbell_csr_addr; int /*<<< orphan*/  backlog_count; int /*<<< orphan*/  pending_count; int /*<<< orphan*/  dma_unaligned; int /*<<< orphan*/  head_unaligned; int /*<<< orphan*/  backlog_qflush; struct nitrox_device* ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV (struct nitrox_device*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmdq_common_cleanup(struct nitrox_cmdq *cmdq)
{
	struct nitrox_device *ndev = cmdq->ndev;

	cancel_work_sync(&cmdq->backlog_qflush);

	dma_free_coherent(DEV(ndev), cmdq->qsize,
			  cmdq->head_unaligned, cmdq->dma_unaligned);

	atomic_set(&cmdq->pending_count, 0);
	atomic_set(&cmdq->backlog_count, 0);

	cmdq->dbell_csr_addr = NULL;
	cmdq->head = NULL;
	cmdq->dma = 0;
	cmdq->qsize = 0;
	cmdq->instr_size = 0;
}