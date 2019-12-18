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
struct cvmx_usb_pipe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_USB_TRANSFER_BULK ; 
 int /*<<< orphan*/  CVMX_USB_TRANSFER_CONTROL ; 
 int /*<<< orphan*/  CVMX_USB_TRANSFER_INTERRUPT ; 
 int /*<<< orphan*/  CVMX_USB_TRANSFER_ISOCHRONOUS ; 
 struct cvmx_usb_pipe* cvmx_usb_find_ready_pipe (struct octeon_hcd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cvmx_usb_pipe *cvmx_usb_next_pipe(struct octeon_hcd *usb,
						int is_sof)
{
	struct cvmx_usb_pipe *pipe;

	/* Find a pipe needing service. */
	if (is_sof) {
		/*
		 * Only process periodic pipes on SOF interrupts. This way we
		 * are sure that the periodic data is sent in the beginning of
		 * the frame.
		 */
		pipe = cvmx_usb_find_ready_pipe(usb,
						CVMX_USB_TRANSFER_ISOCHRONOUS);
		if (pipe)
			return pipe;
		pipe = cvmx_usb_find_ready_pipe(usb,
						CVMX_USB_TRANSFER_INTERRUPT);
		if (pipe)
			return pipe;
	}
	pipe = cvmx_usb_find_ready_pipe(usb, CVMX_USB_TRANSFER_CONTROL);
	if (pipe)
		return pipe;
	return cvmx_usb_find_ready_pipe(usb, CVMX_USB_TRANSFER_BULK);
}