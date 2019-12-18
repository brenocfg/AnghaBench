#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct virt_dma_desc {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  lock; } ;
struct gdma_dmaengine_chan {int next_sg; TYPE_5__ vchan; struct gdma_dma_desc* desc; } ;
struct TYPE_7__ {scalar_t__ cookie; } ;
struct TYPE_8__ {TYPE_1__ tx; } ;
struct gdma_dma_desc {scalar_t__ residue; TYPE_3__* sg; scalar_t__ cyclic; TYPE_2__ vdesc; } ;
struct dma_tx_state {scalar_t__ residue; } ;
struct dma_chan {TYPE_4__* device; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
typedef  scalar_t__ dma_cookie_t ;
struct TYPE_12__ {scalar_t__ residue; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int len; } ;

/* Variables and functions */
 int DMA_COMPLETE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int dma_cookie_status (struct dma_chan*,scalar_t__,struct dma_tx_state*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct gdma_dmaengine_chan* to_gdma_dma_chan (struct dma_chan*) ; 
 TYPE_6__* to_gdma_dma_desc (struct virt_dma_desc*) ; 
 struct virt_dma_desc* vchan_find_desc (TYPE_5__*,scalar_t__) ; 

__attribute__((used)) static enum dma_status gdma_dma_tx_status(struct dma_chan *c,
					  dma_cookie_t cookie,
					  struct dma_tx_state *state)
{
	struct gdma_dmaengine_chan *chan = to_gdma_dma_chan(c);
	struct virt_dma_desc *vdesc;
	enum dma_status status;
	unsigned long flags;
	struct gdma_dma_desc *desc;

	status = dma_cookie_status(c, cookie, state);
	if (status == DMA_COMPLETE || !state)
		return status;

	spin_lock_irqsave(&chan->vchan.lock, flags);
	desc = chan->desc;
	if (desc && (cookie == desc->vdesc.tx.cookie)) {
		/*
		 * We never update edesc->residue in the cyclic case, so we
		 * can tell the remaining room to the end of the circular
		 * buffer.
		 */
		if (desc->cyclic)
			state->residue = desc->residue -
				((chan->next_sg - 1) * desc->sg[0].len);
		else
			state->residue = desc->residue;
	} else {
		vdesc = vchan_find_desc(&chan->vchan, cookie);
		if (vdesc)
			state->residue = to_gdma_dma_desc(vdesc)->residue;
	}
	spin_unlock_irqrestore(&chan->vchan.lock, flags);

	dev_dbg(c->device->dev, "tx residue %d bytes\n", state->residue);

	return status;
}