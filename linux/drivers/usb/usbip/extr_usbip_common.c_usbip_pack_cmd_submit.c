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
struct usbip_header_cmd_submit {int /*<<< orphan*/  interval; int /*<<< orphan*/  number_of_packets; int /*<<< orphan*/  start_frame; int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  transfer_flags; } ;
struct TYPE_2__ {struct usbip_header_cmd_submit cmd_submit; } ;
struct usbip_header {TYPE_1__ u; } ;
struct urb {int /*<<< orphan*/  interval; int /*<<< orphan*/  number_of_packets; int /*<<< orphan*/  start_frame; int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  transfer_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  tweak_transfer_flags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usbip_pack_cmd_submit(struct usbip_header *pdu, struct urb *urb,
				  int pack)
{
	struct usbip_header_cmd_submit *spdu = &pdu->u.cmd_submit;

	/*
	 * Some members are not still implemented in usbip. I hope this issue
	 * will be discussed when usbip is ported to other operating systems.
	 */
	if (pack) {
		spdu->transfer_flags =
			tweak_transfer_flags(urb->transfer_flags);
		spdu->transfer_buffer_length	= urb->transfer_buffer_length;
		spdu->start_frame		= urb->start_frame;
		spdu->number_of_packets		= urb->number_of_packets;
		spdu->interval			= urb->interval;
	} else  {
		urb->transfer_flags         = spdu->transfer_flags;
		urb->transfer_buffer_length = spdu->transfer_buffer_length;
		urb->start_frame            = spdu->start_frame;
		urb->number_of_packets      = spdu->number_of_packets;
		urb->interval               = spdu->interval;
	}
}