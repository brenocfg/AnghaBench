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
struct pl330_dmac {TYPE_1__ ddma; int /*<<< orphan*/  lock; } ;
struct dma_pl330_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  thread; struct pl330_dmac* dmac; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct dma_pl330_chan* to_pchan (struct dma_chan*) ; 

__attribute__((used)) static int pl330_pause(struct dma_chan *chan)
{
	struct dma_pl330_chan *pch = to_pchan(chan);
	struct pl330_dmac *pl330 = pch->dmac;
	unsigned long flags;

	pm_runtime_get_sync(pl330->ddma.dev);
	spin_lock_irqsave(&pch->lock, flags);

	spin_lock(&pl330->lock);
	_stop(pch->thread);
	spin_unlock(&pl330->lock);

	spin_unlock_irqrestore(&pch->lock, flags);
	pm_runtime_mark_last_busy(pl330->ddma.dev);
	pm_runtime_put_autosuspend(pl330->ddma.dev);

	return 0;
}