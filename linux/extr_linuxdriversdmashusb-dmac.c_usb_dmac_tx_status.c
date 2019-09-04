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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct usb_dmac_chan {TYPE_1__ vc; } ;
struct dma_tx_state {int dummy; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 int DMA_COMPLETE ; 
 int dma_cookie_status (struct dma_chan*,int /*<<< orphan*/ ,struct dma_tx_state*) ; 
 int /*<<< orphan*/  dma_set_residue (struct dma_tx_state*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct usb_dmac_chan* to_usb_dmac_chan (struct dma_chan*) ; 
 unsigned int usb_dmac_chan_get_residue (struct usb_dmac_chan*,int /*<<< orphan*/ ) ; 
 unsigned int usb_dmac_chan_get_residue_if_complete (struct usb_dmac_chan*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum dma_status usb_dmac_tx_status(struct dma_chan *chan,
					  dma_cookie_t cookie,
					  struct dma_tx_state *txstate)
{
	struct usb_dmac_chan *uchan = to_usb_dmac_chan(chan);
	enum dma_status status;
	unsigned int residue = 0;
	unsigned long flags;

	status = dma_cookie_status(chan, cookie, txstate);
	/* a client driver will get residue after DMA_COMPLETE */
	if (!txstate)
		return status;

	spin_lock_irqsave(&uchan->vc.lock, flags);
	if (status == DMA_COMPLETE)
		residue = usb_dmac_chan_get_residue_if_complete(uchan, cookie);
	else
		residue = usb_dmac_chan_get_residue(uchan, cookie);
	spin_unlock_irqrestore(&uchan->vc.lock, flags);

	dma_set_residue(txstate, residue);

	return status;
}