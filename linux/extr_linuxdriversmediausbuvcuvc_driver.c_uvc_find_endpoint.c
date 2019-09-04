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
typedef  scalar_t__ u8 ;
struct TYPE_3__ {unsigned int bNumEndpoints; } ;
struct usb_host_interface {struct usb_host_endpoint* endpoint; TYPE_1__ desc; } ;
struct TYPE_4__ {scalar_t__ bEndpointAddress; } ;
struct usb_host_endpoint {TYPE_2__ desc; } ;

/* Variables and functions */

struct usb_host_endpoint *uvc_find_endpoint(struct usb_host_interface *alts,
		u8 epaddr)
{
	struct usb_host_endpoint *ep;
	unsigned int i;

	for (i = 0; i < alts->desc.bNumEndpoints; ++i) {
		ep = &alts->endpoint[i];
		if (ep->desc.bEndpointAddress == epaddr)
			return ep;
	}

	return NULL;
}