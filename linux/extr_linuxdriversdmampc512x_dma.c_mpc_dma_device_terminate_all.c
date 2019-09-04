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
struct mpc_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  free; int /*<<< orphan*/  active; int /*<<< orphan*/  queued; int /*<<< orphan*/  prepared; } ;
struct mpc_dma {TYPE_1__* regs; } ;
struct dma_chan {int /*<<< orphan*/  chan_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  dmacerq; } ;

/* Variables and functions */
 struct mpc_dma* dma_chan_to_mpc_dma (struct dma_chan*) ; 
 struct mpc_dma_chan* dma_chan_to_mpc_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mpc_dma_device_terminate_all(struct dma_chan *chan)
{
	struct mpc_dma_chan *mchan = dma_chan_to_mpc_dma_chan(chan);
	struct mpc_dma *mdma = dma_chan_to_mpc_dma(chan);
	unsigned long flags;

	/* Disable channel requests */
	spin_lock_irqsave(&mchan->lock, flags);

	out_8(&mdma->regs->dmacerq, chan->chan_id);
	list_splice_tail_init(&mchan->prepared, &mchan->free);
	list_splice_tail_init(&mchan->queued, &mchan->free);
	list_splice_tail_init(&mchan->active, &mchan->free);

	spin_unlock_irqrestore(&mchan->lock, flags);

	return 0;
}