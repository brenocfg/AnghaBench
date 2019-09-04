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
typedef  int /*<<< orphan*/  usb_complete_t ;
struct usb_device {int dummy; } ;
struct urb {int number_of_packets; int interval; TYPE_1__* iso_frame_desc; scalar_t__ actual_length; int /*<<< orphan*/  transfer_flags; } ;
struct TYPE_2__ {int offset; int length; scalar_t__ actual_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  URB_ISO_ASAP ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,struct usb_device*,unsigned int,void*,int,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
fill_isoc_urb(struct urb *urb, struct usb_device *dev, unsigned int pipe,
	      void *buf, int num_packets, int packet_size, int interval,
	      usb_complete_t complete, void *context)
{
	int k;

	usb_fill_bulk_urb(urb, dev, pipe, buf, packet_size * num_packets,
			  complete, context);

	urb->number_of_packets = num_packets;
	urb->transfer_flags = URB_ISO_ASAP;
	urb->actual_length = 0;
	urb->interval = interval;

	for (k = 0; k < num_packets; k++) {
		urb->iso_frame_desc[k].offset = packet_size * k;
		urb->iso_frame_desc[k].length = packet_size;
		urb->iso_frame_desc[k].actual_length = 0;
	}
}