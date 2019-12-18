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
struct urb {scalar_t__ transfer_buffer_length; int transfer_flags; int /*<<< orphan*/  num_sgs; TYPE_1__* ep; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 scalar_t__ TRB_IDT_MAX_SIZE ; 
 int URB_NO_TRANSFER_DMA_MAP ; 
 scalar_t__ usb_endpoint_maxp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_endpoint_xfer_isoc (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_urb_dir_out (struct urb*) ; 

__attribute__((used)) static inline bool xhci_urb_suitable_for_idt(struct urb *urb)
{
	if (!usb_endpoint_xfer_isoc(&urb->ep->desc) && usb_urb_dir_out(urb) &&
	    usb_endpoint_maxp(&urb->ep->desc) >= TRB_IDT_MAX_SIZE &&
	    urb->transfer_buffer_length <= TRB_IDT_MAX_SIZE &&
	    !(urb->transfer_flags & URB_NO_TRANSFER_DMA_MAP) &&
	    !urb->num_sgs)
		return true;

	return false;
}