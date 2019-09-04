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
struct usb_dmac_chan {TYPE_1__* desc; int /*<<< orphan*/  vc; } ;
struct TYPE_2__ {scalar_t__ sg_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_usb_dmac_desc (struct virt_dma_desc*) ; 
 int /*<<< orphan*/  usb_dmac_chan_start_sg (struct usb_dmac_chan*,int /*<<< orphan*/ ) ; 
 struct virt_dma_desc* vchan_next_desc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb_dmac_chan_start_desc(struct usb_dmac_chan *chan)
{
	struct virt_dma_desc *vd;

	vd = vchan_next_desc(&chan->vc);
	if (!vd) {
		chan->desc = NULL;
		return;
	}

	/*
	 * Remove this request from vc->desc_issued. Otherwise, this driver
	 * will get the previous value from vchan_next_desc() after a transfer
	 * was completed.
	 */
	list_del(&vd->node);

	chan->desc = to_usb_dmac_desc(vd);
	chan->desc->sg_index = 0;
	usb_dmac_chan_start_sg(chan, 0);
}