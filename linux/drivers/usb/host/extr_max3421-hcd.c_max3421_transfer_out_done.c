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
typedef  scalar_t__ u32 ;
struct usb_hcd {int dummy; } ;
struct urb {scalar_t__ actual_length; scalar_t__ transfer_buffer_length; int transfer_flags; int /*<<< orphan*/  pipe; int /*<<< orphan*/  dev; } ;
struct max3421_hcd {scalar_t__ curr_len; } ;

/* Variables and functions */
 int URB_ZERO_PACKET ; 
 struct max3421_hcd* hcd_to_max3421 (struct usb_hcd*) ; 
 scalar_t__ usb_maxpacket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
max3421_transfer_out_done(struct usb_hcd *hcd, struct urb *urb)
{
	struct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);

	urb->actual_length += max3421_hcd->curr_len;
	if (urb->actual_length < urb->transfer_buffer_length)
		return 0;
	if (urb->transfer_flags & URB_ZERO_PACKET) {
		/*
		 * Some hardware needs a zero-size packet at the end
		 * of a bulk-out transfer if the last transfer was a
		 * full-sized packet (i.e., such hardware use <
		 * max_packet as an indicator that the end of the
		 * packet has been reached).
		 */
		u32 max_packet = usb_maxpacket(urb->dev, urb->pipe, 1);

		if (max3421_hcd->curr_len == max_packet)
			return 0;
	}
	return 1;
}