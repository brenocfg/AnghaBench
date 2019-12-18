#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usb_request {int /*<<< orphan*/  dma; } ;
struct usb_ep {int dummy; } ;
struct nbu2ss_req {struct usb_request req; int /*<<< orphan*/  queue; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ADDR_INVALID ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct nbu2ss_req* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct usb_request *nbu2ss_ep_alloc_request(struct usb_ep *ep,
						   gfp_t gfp_flags)
{
	struct nbu2ss_req *req;

	req = kzalloc(sizeof(*req), gfp_flags);
	if (!req)
		return NULL;

#ifdef USE_DMA
	req->req.dma = DMA_ADDR_INVALID;
#endif
	INIT_LIST_HEAD(&req->queue);

	return &req->req;
}