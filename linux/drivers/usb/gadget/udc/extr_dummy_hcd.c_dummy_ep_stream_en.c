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
struct usb_endpoint_descriptor {int dummy; } ;
struct urb {TYPE_1__* ep; } ;
struct dummy_hcd {int stream_en_ep; } ;
struct TYPE_2__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int dummy_get_ep_idx (struct usb_endpoint_descriptor const*) ; 
 int /*<<< orphan*/  usb_endpoint_xfer_bulk (struct usb_endpoint_descriptor const*) ; 

__attribute__((used)) static int dummy_ep_stream_en(struct dummy_hcd *dum_hcd, struct urb *urb)
{
	const struct usb_endpoint_descriptor *desc = &urb->ep->desc;
	u32 index;

	if (!usb_endpoint_xfer_bulk(desc))
		return 0;

	index = dummy_get_ep_idx(desc);
	return (1 << index) & dum_hcd->stream_en_ep;
}