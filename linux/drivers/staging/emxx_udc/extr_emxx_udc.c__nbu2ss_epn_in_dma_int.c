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
typedef  int u32 ;
struct usb_request {int actual; int length; } ;
struct nbu2ss_udc {int dummy; } ;
struct nbu2ss_req {int dma_flag; scalar_t__ div_len; struct usb_request req; } ;
struct TYPE_2__ {int maxpacket; } ;
struct nbu2ss_ep {int /*<<< orphan*/  epnum; TYPE_1__ ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  _nbu2ss_dma_unmap_single (struct nbu2ss_udc*,struct nbu2ss_ep*,struct nbu2ss_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _nbu2ss_ep_in_end (struct nbu2ss_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _nbu2ss_epn_in_int (struct nbu2ss_udc*,struct nbu2ss_ep*,struct nbu2ss_req*) ; 
 int /*<<< orphan*/  _nbu2ss_epn_in_transfer (struct nbu2ss_udc*,struct nbu2ss_ep*,struct nbu2ss_req*) ; 

__attribute__((used)) static inline void _nbu2ss_epn_in_dma_int(struct nbu2ss_udc *udc,
					  struct nbu2ss_ep *ep,
					  struct nbu2ss_req *req)
{
	u32		mpkt;
	u32		size;
	struct usb_request *preq;

	preq = &req->req;

	if (!req->dma_flag)
		return;

	preq->actual += req->div_len;
	req->div_len = 0;
	req->dma_flag = false;

#ifdef USE_DMA
	_nbu2ss_dma_unmap_single(udc, ep, req, USB_DIR_IN);
#endif

	if (preq->actual != preq->length) {
		_nbu2ss_epn_in_transfer(udc, ep, req);
	} else {
		mpkt = ep->ep.maxpacket;
		size = preq->actual % mpkt;
		if (size > 0) {
			if (((preq->actual & 0x03) == 0) && (size < mpkt))
				_nbu2ss_ep_in_end(udc, ep->epnum, 0, 0);
		} else {
			_nbu2ss_epn_in_int(udc, ep, req);
		}
	}
}