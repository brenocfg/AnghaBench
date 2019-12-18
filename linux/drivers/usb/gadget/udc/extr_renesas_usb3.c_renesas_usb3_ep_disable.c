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
struct usb_ep {int dummy; } ;
struct renesas_usb3_request {int dummy; } ;
struct renesas_usb3_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESHUTDOWN ; 
 int usb3_disable_pipe_n (struct renesas_usb3_ep*) ; 
 int /*<<< orphan*/  usb3_dma_try_stop (struct renesas_usb3_ep*,struct renesas_usb3_request*) ; 
 struct renesas_usb3_request* usb3_get_request (struct renesas_usb3_ep*) ; 
 int /*<<< orphan*/  usb3_request_done (struct renesas_usb3_ep*,struct renesas_usb3_request*,int /*<<< orphan*/ ) ; 
 struct renesas_usb3_ep* usb_ep_to_usb3_ep (struct usb_ep*) ; 

__attribute__((used)) static int renesas_usb3_ep_disable(struct usb_ep *_ep)
{
	struct renesas_usb3_ep *usb3_ep = usb_ep_to_usb3_ep(_ep);
	struct renesas_usb3_request *usb3_req;

	do {
		usb3_req = usb3_get_request(usb3_ep);
		if (!usb3_req)
			break;
		usb3_dma_try_stop(usb3_ep, usb3_req);
		usb3_request_done(usb3_ep, usb3_req, -ESHUTDOWN);
	} while (1);

	return usb3_disable_pipe_n(usb3_ep);
}