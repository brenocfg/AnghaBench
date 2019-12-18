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
struct usbip_device {int dummy; } ;
struct urb {int number_of_packets; int actual_length; scalar_t__ transfer_buffer_length; TYPE_1__* iso_frame_desc; scalar_t__ transfer_buffer; int /*<<< orphan*/  pipe; } ;
struct TYPE_2__ {scalar_t__ actual_length; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  usb_pipeisoc (int /*<<< orphan*/ ) ; 

void usbip_pad_iso(struct usbip_device *ud, struct urb *urb)
{
	int np = urb->number_of_packets;
	int i;
	int actualoffset = urb->actual_length;

	if (!usb_pipeisoc(urb->pipe))
		return;

	/* if no packets or length of data is 0, then nothing to unpack */
	if (np == 0 || urb->actual_length == 0)
		return;

	/*
	 * if actual_length is transfer_buffer_length then no padding is
	 * present.
	 */
	if (urb->actual_length == urb->transfer_buffer_length)
		return;

	/*
	 * loop over all packets from last to first (to prevent overwriting
	 * memory when padding) and move them into the proper place
	 */
	for (i = np-1; i > 0; i--) {
		actualoffset -= urb->iso_frame_desc[i].actual_length;
		memmove(urb->transfer_buffer + urb->iso_frame_desc[i].offset,
			urb->transfer_buffer + actualoffset,
			urb->iso_frame_desc[i].actual_length);
	}
}