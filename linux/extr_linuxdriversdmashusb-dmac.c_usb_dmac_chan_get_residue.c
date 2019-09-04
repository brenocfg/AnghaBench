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
typedef  int /*<<< orphan*/  u32 ;
struct virt_dma_desc {int dummy; } ;
struct usb_dmac_desc {int sg_index; int sg_len; TYPE_1__* sg; } ;
struct usb_dmac_chan {int /*<<< orphan*/  vc; struct usb_dmac_desc* desc; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;
struct TYPE_2__ {scalar_t__ size; } ;

/* Variables and functions */
 struct usb_dmac_desc* to_usb_dmac_desc (struct virt_dma_desc*) ; 
 scalar_t__ usb_dmac_get_current_residue (struct usb_dmac_chan*,struct usb_dmac_desc*,int) ; 
 struct virt_dma_desc* vchan_find_desc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 usb_dmac_chan_get_residue(struct usb_dmac_chan *chan,
				     dma_cookie_t cookie)
{
	u32 residue = 0;
	struct virt_dma_desc *vd;
	struct usb_dmac_desc *desc = chan->desc;
	int i;

	if (!desc) {
		vd = vchan_find_desc(&chan->vc, cookie);
		if (!vd)
			return 0;
		desc = to_usb_dmac_desc(vd);
	}

	/* Compute the size of all usb_dmac_sg still to be transferred */
	for (i = desc->sg_index + 1; i < desc->sg_len; i++)
		residue += desc->sg[i].size;

	/* Add the residue for the current sg */
	residue += usb_dmac_get_current_residue(chan, desc, desc->sg_index);

	return residue;
}