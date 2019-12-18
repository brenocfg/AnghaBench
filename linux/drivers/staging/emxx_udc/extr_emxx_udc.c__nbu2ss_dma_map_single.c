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
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;
struct nbu2ss_udc {TYPE_2__ gadget; } ;
struct TYPE_6__ {scalar_t__ dma; int /*<<< orphan*/  length; int /*<<< orphan*/  buf; } ;
struct nbu2ss_req {int mapped; TYPE_3__ req; scalar_t__ unaligned; } ;
struct nbu2ss_ep {scalar_t__ phys_buf; } ;

/* Variables and functions */
 scalar_t__ DMA_ADDR_INVALID ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ USB_DIR_IN ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _nbu2ss_dma_map_single(struct nbu2ss_udc *udc,
				   struct nbu2ss_ep *ep,
				   struct nbu2ss_req *req, u8 direct)
{
	if (req->req.dma == DMA_ADDR_INVALID) {
		if (req->unaligned) {
			req->req.dma = ep->phys_buf;
		} else {
			req->req.dma = dma_map_single(udc->gadget.dev.parent,
						      req->req.buf,
						      req->req.length,
						      (direct == USB_DIR_IN)
						      ? DMA_TO_DEVICE
						      : DMA_FROM_DEVICE);
		}
		req->mapped = 1;
	} else {
		if (!req->unaligned)
			dma_sync_single_for_device(udc->gadget.dev.parent,
						   req->req.dma,
						   req->req.length,
						   (direct == USB_DIR_IN)
						   ? DMA_TO_DEVICE
						   : DMA_FROM_DEVICE);

		req->mapped = 0;
	}
}