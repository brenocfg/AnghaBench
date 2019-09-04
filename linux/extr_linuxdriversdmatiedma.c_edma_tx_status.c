#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct virt_dma_desc {int /*<<< orphan*/  tx; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct edma_chan {TYPE_3__ vchan; TYPE_5__* edesc; } ;
struct dma_tx_state {int /*<<< orphan*/  residue; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
typedef  scalar_t__ dma_cookie_t ;
struct TYPE_6__ {scalar_t__ cookie; } ;
struct TYPE_7__ {TYPE_1__ tx; } ;
struct TYPE_10__ {TYPE_2__ vdesc; } ;
struct TYPE_9__ {int /*<<< orphan*/  residue; } ;

/* Variables and functions */
 int DMA_COMPLETE ; 
 int dma_cookie_status (struct dma_chan*,scalar_t__,struct dma_tx_state*) ; 
 int /*<<< orphan*/  edma_residue (TYPE_5__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct edma_chan* to_edma_chan (struct dma_chan*) ; 
 TYPE_4__* to_edma_desc (int /*<<< orphan*/ *) ; 
 struct virt_dma_desc* vchan_find_desc (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static enum dma_status edma_tx_status(struct dma_chan *chan,
				      dma_cookie_t cookie,
				      struct dma_tx_state *txstate)
{
	struct edma_chan *echan = to_edma_chan(chan);
	struct virt_dma_desc *vdesc;
	enum dma_status ret;
	unsigned long flags;

	ret = dma_cookie_status(chan, cookie, txstate);
	if (ret == DMA_COMPLETE || !txstate)
		return ret;

	spin_lock_irqsave(&echan->vchan.lock, flags);
	if (echan->edesc && echan->edesc->vdesc.tx.cookie == cookie)
		txstate->residue = edma_residue(echan->edesc);
	else if ((vdesc = vchan_find_desc(&echan->vchan, cookie)))
		txstate->residue = to_edma_desc(&vdesc->tx)->residue;
	spin_unlock_irqrestore(&echan->vchan.lock, flags);

	return ret;
}