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
struct dma_chan {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {struct dma_chan chan; } ;
struct usb_dmac_chan {TYPE_1__ vc; } ;
struct usb_dmac {int n_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_DMAOR ; 
 int /*<<< orphan*/  USB_DMASWR ; 
 int USB_DMASWR_SWR ; 
 struct usb_dmac* to_usb_dmac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ usb_dmac_chan_is_busy (struct usb_dmac_chan*) ; 
 int /*<<< orphan*/  usb_dmac_write (struct usb_dmac*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void usb_dmac_soft_reset(struct usb_dmac_chan *uchan)
{
	struct dma_chan *chan = &uchan->vc.chan;
	struct usb_dmac *dmac = to_usb_dmac(chan->device);
	int i;

	/* Don't issue soft reset if any one of channels is busy */
	for (i = 0; i < dmac->n_channels; ++i) {
		if (usb_dmac_chan_is_busy(uchan))
			return;
	}

	usb_dmac_write(dmac, USB_DMAOR, 0);
	usb_dmac_write(dmac, USB_DMASWR, USB_DMASWR_SWR);
	udelay(100);
	usb_dmac_write(dmac, USB_DMASWR, 0);
	usb_dmac_write(dmac, USB_DMAOR, 1);
}