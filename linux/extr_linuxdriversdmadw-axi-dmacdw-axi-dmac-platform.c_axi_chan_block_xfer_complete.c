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
struct virt_dma_desc {int /*<<< orphan*/  node; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct axi_dma_chan {TYPE_1__ vc; } ;

/* Variables and functions */
 int /*<<< orphan*/  axi_chan_disable (struct axi_dma_chan*) ; 
 int /*<<< orphan*/  axi_chan_is_hw_enable (struct axi_dma_chan*) ; 
 int /*<<< orphan*/  axi_chan_name (struct axi_dma_chan*) ; 
 int /*<<< orphan*/  axi_chan_start_first_queued (struct axi_dma_chan*) ; 
 int /*<<< orphan*/  chan2dev (struct axi_dma_chan*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchan_cookie_complete (struct virt_dma_desc*) ; 
 struct virt_dma_desc* vchan_next_desc (TYPE_1__*) ; 

__attribute__((used)) static void axi_chan_block_xfer_complete(struct axi_dma_chan *chan)
{
	struct virt_dma_desc *vd;
	unsigned long flags;

	spin_lock_irqsave(&chan->vc.lock, flags);
	if (unlikely(axi_chan_is_hw_enable(chan))) {
		dev_err(chan2dev(chan), "BUG: %s caught DWAXIDMAC_IRQ_DMA_TRF, but channel not idle!\n",
			axi_chan_name(chan));
		axi_chan_disable(chan);
	}

	/* The completed descriptor currently is in the head of vc list */
	vd = vchan_next_desc(&chan->vc);
	/* Remove the completed descriptor from issued list before completing */
	list_del(&vd->node);
	vchan_cookie_complete(vd);

	/* Submit queued descriptors after processing the completed ones */
	axi_chan_start_first_queued(chan);

	spin_unlock_irqrestore(&chan->vc.lock, flags);
}