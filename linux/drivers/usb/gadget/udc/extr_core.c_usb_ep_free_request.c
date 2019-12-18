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
struct usb_ep {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_request ) (struct usb_ep*,struct usb_request*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct usb_ep*,struct usb_request*) ; 
 int /*<<< orphan*/  trace_usb_ep_free_request (struct usb_ep*,struct usb_request*,int /*<<< orphan*/ ) ; 

void usb_ep_free_request(struct usb_ep *ep,
				       struct usb_request *req)
{
	trace_usb_ep_free_request(ep, req, 0);
	ep->ops->free_request(ep, req);
}