#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct usb_dmac_chan {TYPE_2__ vc; } ;
struct dma_chan {TYPE_1__* device; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct usb_dmac_chan* to_usb_dmac_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  usb_dmac_chan_halt (struct usb_dmac_chan*) ; 
 int /*<<< orphan*/  usb_dmac_desc_free (struct usb_dmac_chan*) ; 
 int /*<<< orphan*/  vchan_free_chan_resources (TYPE_2__*) ; 

__attribute__((used)) static void usb_dmac_free_chan_resources(struct dma_chan *chan)
{
	struct usb_dmac_chan *uchan = to_usb_dmac_chan(chan);
	unsigned long flags;

	/* Protect against ISR */
	spin_lock_irqsave(&uchan->vc.lock, flags);
	usb_dmac_chan_halt(uchan);
	spin_unlock_irqrestore(&uchan->vc.lock, flags);

	usb_dmac_desc_free(uchan);
	vchan_free_chan_resources(&uchan->vc);

	pm_runtime_put(chan->device->dev);
}