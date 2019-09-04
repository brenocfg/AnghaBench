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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct pl330_dmac {TYPE_1__ ddma; int /*<<< orphan*/  lock; int /*<<< orphan*/  desc_pool; } ;
struct dma_pl330_chan {struct pl330_dmac* dmac; int /*<<< orphan*/  work_list; scalar_t__ cyclic; int /*<<< orphan*/ * thread; int /*<<< orphan*/  task; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pl330_release_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pl330_unprep_slave_fifo (struct dma_pl330_chan*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 struct dma_pl330_chan* to_pchan (struct dma_chan*) ; 

__attribute__((used)) static void pl330_free_chan_resources(struct dma_chan *chan)
{
	struct dma_pl330_chan *pch = to_pchan(chan);
	struct pl330_dmac *pl330 = pch->dmac;
	unsigned long flags;

	tasklet_kill(&pch->task);

	pm_runtime_get_sync(pch->dmac->ddma.dev);
	spin_lock_irqsave(&pl330->lock, flags);

	pl330_release_channel(pch->thread);
	pch->thread = NULL;

	if (pch->cyclic)
		list_splice_tail_init(&pch->work_list, &pch->dmac->desc_pool);

	spin_unlock_irqrestore(&pl330->lock, flags);
	pm_runtime_mark_last_busy(pch->dmac->ddma.dev);
	pm_runtime_put_autosuspend(pch->dmac->ddma.dev);
	pl330_unprep_slave_fifo(pch);
}