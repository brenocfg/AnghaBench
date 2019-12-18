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
struct TYPE_2__ {int /*<<< orphan*/  epdir; } ;
union cvmx_usbcx_hccharx {TYPE_1__ s; } ;
struct usb_ctrlrequest {int /*<<< orphan*/  wLength; } ;
struct octeon_hcd {int dummy; } ;
struct cvmx_usb_transaction {int stage; int actual_bytes; int /*<<< orphan*/  control_header; } ;
struct cvmx_usb_pipe {int pid_toggle; int max_packet; } ;

/* Variables and functions */
#define  CVMX_USB_STAGE_DATA 135 
#define  CVMX_USB_STAGE_DATA_SPLIT_COMPLETE 134 
#define  CVMX_USB_STAGE_NON_CONTROL 133 
#define  CVMX_USB_STAGE_NON_CONTROL_SPLIT_COMPLETE 132 
#define  CVMX_USB_STAGE_SETUP 131 
#define  CVMX_USB_STAGE_SETUP_SPLIT_COMPLETE 130 
#define  CVMX_USB_STAGE_STATUS 129 
#define  CVMX_USB_STAGE_STATUS_SPLIT_COMPLETE 128 
 int /*<<< orphan*/  CVMX_USB_STATUS_ERROR ; 
 int /*<<< orphan*/  CVMX_USB_STATUS_OK ; 
 struct usb_ctrlrequest* cvmx_phys_to_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_usb_complete (struct octeon_hcd*,struct cvmx_usb_pipe*,struct cvmx_usb_transaction*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_usb_pipe_needs_split (struct octeon_hcd*,struct cvmx_usb_pipe*) ; 

__attribute__((used)) static void cvmx_usb_transfer_control(struct octeon_hcd *usb,
				      struct cvmx_usb_pipe *pipe,
				      struct cvmx_usb_transaction *transaction,
				      union cvmx_usbcx_hccharx usbc_hcchar,
				      int buffer_space_left,
				      int bytes_in_last_packet)
{
	switch (transaction->stage) {
	case CVMX_USB_STAGE_NON_CONTROL:
	case CVMX_USB_STAGE_NON_CONTROL_SPLIT_COMPLETE:
		/* This should be impossible */
		cvmx_usb_complete(usb, pipe, transaction,
				  CVMX_USB_STATUS_ERROR);
		break;
	case CVMX_USB_STAGE_SETUP:
		pipe->pid_toggle = 1;
		if (cvmx_usb_pipe_needs_split(usb, pipe)) {
			transaction->stage =
				CVMX_USB_STAGE_SETUP_SPLIT_COMPLETE;
		} else {
			struct usb_ctrlrequest *header =
				cvmx_phys_to_ptr(transaction->control_header);
			if (header->wLength)
				transaction->stage = CVMX_USB_STAGE_DATA;
			else
				transaction->stage = CVMX_USB_STAGE_STATUS;
		}
		break;
	case CVMX_USB_STAGE_SETUP_SPLIT_COMPLETE:
		{
			struct usb_ctrlrequest *header =
				cvmx_phys_to_ptr(transaction->control_header);
			if (header->wLength)
				transaction->stage = CVMX_USB_STAGE_DATA;
			else
				transaction->stage = CVMX_USB_STAGE_STATUS;
		}
		break;
	case CVMX_USB_STAGE_DATA:
		if (cvmx_usb_pipe_needs_split(usb, pipe)) {
			transaction->stage = CVMX_USB_STAGE_DATA_SPLIT_COMPLETE;
			/*
			 * For setup OUT data that are splits,
			 * the hardware doesn't appear to count
			 * transferred data. Here we manually
			 * update the data transferred
			 */
			if (!usbc_hcchar.s.epdir) {
				if (buffer_space_left < pipe->max_packet)
					transaction->actual_bytes +=
						buffer_space_left;
				else
					transaction->actual_bytes +=
						pipe->max_packet;
			}
		} else if ((buffer_space_left == 0) ||
			   (bytes_in_last_packet < pipe->max_packet)) {
			pipe->pid_toggle = 1;
			transaction->stage = CVMX_USB_STAGE_STATUS;
		}
		break;
	case CVMX_USB_STAGE_DATA_SPLIT_COMPLETE:
		if ((buffer_space_left == 0) ||
		    (bytes_in_last_packet < pipe->max_packet)) {
			pipe->pid_toggle = 1;
			transaction->stage = CVMX_USB_STAGE_STATUS;
		} else {
			transaction->stage = CVMX_USB_STAGE_DATA;
		}
		break;
	case CVMX_USB_STAGE_STATUS:
		if (cvmx_usb_pipe_needs_split(usb, pipe))
			transaction->stage =
				CVMX_USB_STAGE_STATUS_SPLIT_COMPLETE;
		else
			cvmx_usb_complete(usb, pipe, transaction,
					  CVMX_USB_STATUS_OK);
		break;
	case CVMX_USB_STAGE_STATUS_SPLIT_COMPLETE:
		cvmx_usb_complete(usb, pipe, transaction, CVMX_USB_STATUS_OK);
		break;
	}
}