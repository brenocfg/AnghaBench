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
struct urb {int /*<<< orphan*/  number_of_packets; int /*<<< orphan*/  start_frame; int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  transfer_dma; scalar_t__ setup_packet; } ;
struct octeon_hcd {int dummy; } ;
struct cvmx_usb_transaction {int dummy; } ;
struct cvmx_usb_pipe {int dummy; } ;
struct cvmx_usb_iso_packet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_USB_TRANSFER_ISOCHRONOUS ; 
 struct cvmx_usb_transaction* cvmx_usb_submit_transaction (struct octeon_hcd*,struct cvmx_usb_pipe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cvmx_usb_iso_packet*,struct urb*) ; 

__attribute__((used)) static struct cvmx_usb_transaction *cvmx_usb_submit_isochronous(
						struct octeon_hcd *usb,
						struct cvmx_usb_pipe *pipe,
						struct urb *urb)
{
	struct cvmx_usb_iso_packet *packets;

	packets = (struct cvmx_usb_iso_packet *)urb->setup_packet;
	return cvmx_usb_submit_transaction(usb, pipe,
					   CVMX_USB_TRANSFER_ISOCHRONOUS,
					   urb->transfer_dma,
					   urb->transfer_buffer_length,
					   0, /* control_header */
					   urb->start_frame,
					   urb->number_of_packets,
					   packets, urb);
}