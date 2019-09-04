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
struct TYPE_2__ {int /*<<< orphan*/  chan; } ;
struct virt_dma_desc {TYPE_1__ tx; } ;
struct usb_dmac_desc {int dummy; } ;
struct usb_dmac_chan {int dummy; } ;

/* Variables and functions */
 struct usb_dmac_chan* to_usb_dmac_chan (int /*<<< orphan*/ ) ; 
 struct usb_dmac_desc* to_usb_dmac_desc (struct virt_dma_desc*) ; 
 int /*<<< orphan*/  usb_dmac_desc_put (struct usb_dmac_chan*,struct usb_dmac_desc*) ; 

__attribute__((used)) static void usb_dmac_virt_desc_free(struct virt_dma_desc *vd)
{
	struct usb_dmac_desc *desc = to_usb_dmac_desc(vd);
	struct usb_dmac_chan *chan = to_usb_dmac_chan(vd->tx.chan);

	usb_dmac_desc_put(chan, desc);
}