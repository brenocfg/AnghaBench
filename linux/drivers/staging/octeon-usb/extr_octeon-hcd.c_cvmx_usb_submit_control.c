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
typedef  int /*<<< orphan*/  u64 ;
struct usb_ctrlrequest {int bRequestType; int /*<<< orphan*/  wLength; } ;
struct urb {int transfer_buffer_length; int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  setup_dma; } ;
struct octeon_hcd {int dummy; } ;
struct cvmx_usb_transaction {int dummy; } ;
struct cvmx_usb_pipe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_USB_TRANSFER_CONTROL ; 
 int USB_DIR_IN ; 
 struct usb_ctrlrequest* cvmx_phys_to_ptr (int /*<<< orphan*/ ) ; 
 struct cvmx_usb_transaction* cvmx_usb_submit_transaction (struct octeon_hcd*,struct cvmx_usb_pipe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct urb*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cvmx_usb_transaction *cvmx_usb_submit_control(
						struct octeon_hcd *usb,
						struct cvmx_usb_pipe *pipe,
						struct urb *urb)
{
	int buffer_length = urb->transfer_buffer_length;
	u64 control_header = urb->setup_dma;
	struct usb_ctrlrequest *header = cvmx_phys_to_ptr(control_header);

	if ((header->bRequestType & USB_DIR_IN) == 0)
		buffer_length = le16_to_cpu(header->wLength);

	return cvmx_usb_submit_transaction(usb, pipe,
					   CVMX_USB_TRANSFER_CONTROL,
					   urb->transfer_dma, buffer_length,
					   control_header,
					   0, /* iso_start_frame */
					   0, /* iso_number_packets */
					   NULL, /* iso_packets */
					   urb);
}