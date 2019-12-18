#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;
struct nbu2ss_udc {TYPE_2__ gadget; } ;
struct TYPE_6__ {int actual; scalar_t__* buf; int /*<<< orphan*/  length; int /*<<< orphan*/  dma; } ;
struct nbu2ss_req {TYPE_3__ req; scalar_t__ unaligned; scalar_t__ mapped; } ;
struct nbu2ss_ep {scalar_t__* virt_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ADDR_INVALID ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ USB_DIR_IN ; 
 scalar_t__ USB_DIR_OUT ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static void _nbu2ss_dma_unmap_single(struct nbu2ss_udc *udc,
				     struct nbu2ss_ep *ep,
				     struct nbu2ss_req *req, u8 direct)
{
	u8		data[4];
	u8		*p;
	u32		count = 0;

	if (direct == USB_DIR_OUT) {
		count = req->req.actual % 4;
		if (count) {
			p = req->req.buf;
			p += (req->req.actual - count);
			memcpy(data, p, count);
		}
	}

	if (req->mapped) {
		if (req->unaligned) {
			if (direct == USB_DIR_OUT)
				memcpy(req->req.buf, ep->virt_buf,
				       req->req.actual & 0xfffffffc);
		} else {
			dma_unmap_single(udc->gadget.dev.parent,
					 req->req.dma, req->req.length,
				(direct == USB_DIR_IN)
				? DMA_TO_DEVICE
				: DMA_FROM_DEVICE);
		}
		req->req.dma = DMA_ADDR_INVALID;
		req->mapped = 0;
	} else {
		if (!req->unaligned)
			dma_sync_single_for_cpu(udc->gadget.dev.parent,
						req->req.dma, req->req.length,
				(direct == USB_DIR_IN)
				? DMA_TO_DEVICE
				: DMA_FROM_DEVICE);
	}

	if (count) {
		p = req->req.buf;
		p += (req->req.actual - count);
		memcpy(p, data, count);
	}
}