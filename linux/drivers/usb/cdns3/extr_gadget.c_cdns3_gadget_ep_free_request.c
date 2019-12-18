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
struct usb_request {int dummy; } ;
struct usb_ep {int dummy; } ;
struct cdns3_request {TYPE_1__* aligned_buf; } ;
struct TYPE_2__ {scalar_t__ in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct cdns3_request*) ; 
 struct cdns3_request* to_cdns3_request (struct usb_request*) ; 
 int /*<<< orphan*/  trace_cdns3_free_request (struct cdns3_request*) ; 

void cdns3_gadget_ep_free_request(struct usb_ep *ep,
				  struct usb_request *request)
{
	struct cdns3_request *priv_req = to_cdns3_request(request);

	if (priv_req->aligned_buf)
		priv_req->aligned_buf->in_use = 0;

	trace_cdns3_free_request(priv_req);
	kfree(priv_req);
}