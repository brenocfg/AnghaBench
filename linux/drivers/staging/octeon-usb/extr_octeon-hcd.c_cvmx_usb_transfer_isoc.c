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
struct octeon_hcd {int dummy; } ;
struct cvmx_usb_transaction {scalar_t__ stage; } ;
struct cvmx_usb_pipe {scalar_t__ transfer_dir; int max_packet; scalar_t__ interval; int /*<<< orphan*/  next_tx_frame; } ;

/* Variables and functions */
 scalar_t__ CVMX_USB_DIRECTION_OUT ; 
 scalar_t__ CVMX_USB_STAGE_NON_CONTROL_SPLIT_COMPLETE ; 
 int /*<<< orphan*/  CVMX_USB_STATUS_OK ; 
 int /*<<< orphan*/  cvmx_usb_complete (struct octeon_hcd*,struct cvmx_usb_pipe*,struct cvmx_usb_transaction*,int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_usb_pipe_needs_split (struct octeon_hcd*,struct cvmx_usb_pipe*) ; 

__attribute__((used)) static void cvmx_usb_transfer_isoc(struct octeon_hcd *usb,
				   struct cvmx_usb_pipe *pipe,
				   struct cvmx_usb_transaction *transaction,
				   int buffer_space_left,
				   int bytes_in_last_packet,
				   int bytes_this_transfer)
{
	if (cvmx_usb_pipe_needs_split(usb, pipe)) {
		/*
		 * ISOCHRONOUS OUT splits don't require a complete split stage.
		 * Instead they use a sequence of begin OUT splits to transfer
		 * the data 188 bytes at a time. Once the transfer is complete,
		 * the pipe sleeps until the next schedule interval.
		 */
		if (pipe->transfer_dir == CVMX_USB_DIRECTION_OUT) {
			/*
			 * If no space left or this wasn't a max size packet
			 * then this transfer is complete. Otherwise start it
			 * again to send the next 188 bytes
			 */
			if (!buffer_space_left || (bytes_this_transfer < 188)) {
				pipe->next_tx_frame += pipe->interval;
				cvmx_usb_complete(usb, pipe, transaction,
						  CVMX_USB_STATUS_OK);
			}
			return;
		}
		if (transaction->stage ==
		    CVMX_USB_STAGE_NON_CONTROL_SPLIT_COMPLETE) {
			/*
			 * We are in the incoming data phase. Keep getting data
			 * until we run out of space or get a small packet
			 */
			if ((buffer_space_left == 0) ||
			    (bytes_in_last_packet < pipe->max_packet)) {
				pipe->next_tx_frame += pipe->interval;
				cvmx_usb_complete(usb, pipe, transaction,
						  CVMX_USB_STATUS_OK);
			}
		} else {
			transaction->stage =
				CVMX_USB_STAGE_NON_CONTROL_SPLIT_COMPLETE;
		}
	} else {
		pipe->next_tx_frame += pipe->interval;
		cvmx_usb_complete(usb, pipe, transaction, CVMX_USB_STATUS_OK);
	}
}