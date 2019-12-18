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
struct xhci_td {struct urb* urb; struct xhci_segment* bounce_seg; } ;
struct xhci_segment {size_t bounce_len; scalar_t__ bounce_offs; int /*<<< orphan*/  bounce_buf; int /*<<< orphan*/  bounce_dma; } ;
struct xhci_ring {int /*<<< orphan*/  bounce_buf_len; } ;
struct xhci_hcd {int dummy; } ;
struct urb {int /*<<< orphan*/  num_sgs; int /*<<< orphan*/  sg; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device* controller; } ;
struct TYPE_4__ {TYPE_1__ self; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t sg_pcopy_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,scalar_t__) ; 
 scalar_t__ usb_urb_dir_out (struct urb*) ; 
 TYPE_2__* xhci_to_hcd (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*,size_t,size_t) ; 

__attribute__((used)) static void xhci_unmap_td_bounce_buffer(struct xhci_hcd *xhci,
		struct xhci_ring *ring, struct xhci_td *td)
{
	struct device *dev = xhci_to_hcd(xhci)->self.controller;
	struct xhci_segment *seg = td->bounce_seg;
	struct urb *urb = td->urb;
	size_t len;

	if (!ring || !seg || !urb)
		return;

	if (usb_urb_dir_out(urb)) {
		dma_unmap_single(dev, seg->bounce_dma, ring->bounce_buf_len,
				 DMA_TO_DEVICE);
		return;
	}

	dma_unmap_single(dev, seg->bounce_dma, ring->bounce_buf_len,
			 DMA_FROM_DEVICE);
	/* for in tranfers we need to copy the data from bounce to sg */
	len = sg_pcopy_from_buffer(urb->sg, urb->num_sgs, seg->bounce_buf,
			     seg->bounce_len, seg->bounce_offs);
	if (len != seg->bounce_len)
		xhci_warn(xhci, "WARN Wrong bounce buffer read length: %zu != %d\n",
				len, seg->bounce_len);
	seg->bounce_len = 0;
	seg->bounce_offs = 0;
}