#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct virt_dma_desc {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct stm32_mdma_chan {TYPE_3__ vchan; int /*<<< orphan*/  curr_hwdesc; TYPE_4__* desc; } ;
struct dma_tx_state {int dummy; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
typedef  scalar_t__ dma_cookie_t ;
struct TYPE_6__ {scalar_t__ cookie; } ;
struct TYPE_7__ {TYPE_1__ tx; } ;
struct TYPE_9__ {TYPE_2__ vdesc; } ;

/* Variables and functions */
 int DMA_COMPLETE ; 
 int dma_cookie_status (struct dma_chan*,scalar_t__,struct dma_tx_state*) ; 
 int /*<<< orphan*/  dma_set_residue (struct dma_tx_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stm32_mdma_desc_residue (struct stm32_mdma_chan*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 struct stm32_mdma_chan* to_stm32_mdma_chan (struct dma_chan*) ; 
 TYPE_4__* to_stm32_mdma_desc (struct virt_dma_desc*) ; 
 struct virt_dma_desc* vchan_find_desc (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static enum dma_status stm32_mdma_tx_status(struct dma_chan *c,
					    dma_cookie_t cookie,
					    struct dma_tx_state *state)
{
	struct stm32_mdma_chan *chan = to_stm32_mdma_chan(c);
	struct virt_dma_desc *vdesc;
	enum dma_status status;
	unsigned long flags;
	u32 residue = 0;

	status = dma_cookie_status(c, cookie, state);
	if ((status == DMA_COMPLETE) || (!state))
		return status;

	spin_lock_irqsave(&chan->vchan.lock, flags);

	vdesc = vchan_find_desc(&chan->vchan, cookie);
	if (chan->desc && cookie == chan->desc->vdesc.tx.cookie)
		residue = stm32_mdma_desc_residue(chan, chan->desc,
						  chan->curr_hwdesc);
	else if (vdesc)
		residue = stm32_mdma_desc_residue(chan,
						  to_stm32_mdma_desc(vdesc), 0);
	dma_set_residue(state, residue);

	spin_unlock_irqrestore(&chan->vchan.lock, flags);

	return status;
}