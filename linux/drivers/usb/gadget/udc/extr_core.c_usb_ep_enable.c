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
struct usb_ep {int enabled; int /*<<< orphan*/  desc; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* enable ) (struct usb_ep*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct usb_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_usb_ep_enable (struct usb_ep*,int) ; 
 scalar_t__ usb_endpoint_maxp (int /*<<< orphan*/ ) ; 

int usb_ep_enable(struct usb_ep *ep)
{
	int ret = 0;

	if (ep->enabled)
		goto out;

	/* UDC drivers can't handle endpoints with maxpacket size 0 */
	if (usb_endpoint_maxp(ep->desc) == 0) {
		/*
		 * We should log an error message here, but we can't call
		 * dev_err() because there's no way to find the gadget
		 * given only ep.
		 */
		ret = -EINVAL;
		goto out;
	}

	ret = ep->ops->enable(ep, ep->desc);
	if (ret)
		goto out;

	ep->enabled = true;

out:
	trace_usb_ep_enable(ep, ret);

	return ret;
}