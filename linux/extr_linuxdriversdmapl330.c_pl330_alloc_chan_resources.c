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
struct pl330_dmac {int /*<<< orphan*/  lock; } ;
struct dma_pl330_chan {int cyclic; int /*<<< orphan*/  task; int /*<<< orphan*/  thread; struct pl330_dmac* dmac; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dma_cookie_init (struct dma_chan*) ; 
 int /*<<< orphan*/  pl330_request_channel (struct pl330_dmac*) ; 
 int /*<<< orphan*/  pl330_tasklet ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 struct dma_pl330_chan* to_pchan (struct dma_chan*) ; 

__attribute__((used)) static int pl330_alloc_chan_resources(struct dma_chan *chan)
{
	struct dma_pl330_chan *pch = to_pchan(chan);
	struct pl330_dmac *pl330 = pch->dmac;
	unsigned long flags;

	spin_lock_irqsave(&pl330->lock, flags);

	dma_cookie_init(chan);
	pch->cyclic = false;

	pch->thread = pl330_request_channel(pl330);
	if (!pch->thread) {
		spin_unlock_irqrestore(&pl330->lock, flags);
		return -ENOMEM;
	}

	tasklet_init(&pch->task, pl330_tasklet, (unsigned long) pch);

	spin_unlock_irqrestore(&pl330->lock, flags);

	return 1;
}