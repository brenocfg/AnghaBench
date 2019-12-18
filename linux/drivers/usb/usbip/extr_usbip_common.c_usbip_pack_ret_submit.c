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
struct usbip_header_ret_submit {int /*<<< orphan*/  error_count; int /*<<< orphan*/  number_of_packets; int /*<<< orphan*/  start_frame; int /*<<< orphan*/  actual_length; int /*<<< orphan*/  status; } ;
struct TYPE_2__ {struct usbip_header_ret_submit ret_submit; } ;
struct usbip_header {TYPE_1__ u; } ;
struct urb {int /*<<< orphan*/  error_count; int /*<<< orphan*/  number_of_packets; int /*<<< orphan*/  start_frame; int /*<<< orphan*/  actual_length; int /*<<< orphan*/  status; } ;

/* Variables and functions */

__attribute__((used)) static void usbip_pack_ret_submit(struct usbip_header *pdu, struct urb *urb,
				  int pack)
{
	struct usbip_header_ret_submit *rpdu = &pdu->u.ret_submit;

	if (pack) {
		rpdu->status		= urb->status;
		rpdu->actual_length	= urb->actual_length;
		rpdu->start_frame	= urb->start_frame;
		rpdu->number_of_packets = urb->number_of_packets;
		rpdu->error_count	= urb->error_count;
	} else {
		urb->status		= rpdu->status;
		urb->actual_length	= rpdu->actual_length;
		urb->start_frame	= rpdu->start_frame;
		urb->number_of_packets = rpdu->number_of_packets;
		urb->error_count	= rpdu->error_count;
	}
}