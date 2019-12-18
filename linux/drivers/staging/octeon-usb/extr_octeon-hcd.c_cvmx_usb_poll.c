#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ prtena; } ;
union cvmx_usbcx_hprt {void* u32; TYPE_2__ s; } ;
struct TYPE_4__ {int frnum; } ;
union cvmx_usbcx_hfnum {TYPE_1__ s; void* u32; } ;
union cvmx_usbcx_haint {int u32; } ;
struct TYPE_6__ {int /*<<< orphan*/  sof; scalar_t__ hchint; scalar_t__ prtint; scalar_t__ disconnint; scalar_t__ nptxfemp; scalar_t__ ptxfemp; scalar_t__ rxflvl; } ;
union cvmx_usbcx_gintsts {TYPE_3__ s; void* u32; } ;
struct octeon_hcd {int frame_number; int init_flags; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_USBCX_GINTSTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_USBCX_HAINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_USBCX_HFNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_USBCX_HPRT (int /*<<< orphan*/ ) ; 
 int CVMX_USB_INITIALIZE_FLAGS_NO_DMA ; 
 int __fls (int) ; 
 int /*<<< orphan*/  cvmx_usb_poll_channel (struct octeon_hcd*,int) ; 
 int /*<<< orphan*/  cvmx_usb_poll_rx_fifo (struct octeon_hcd*) ; 
 int /*<<< orphan*/  cvmx_usb_poll_tx_fifo (struct octeon_hcd*) ; 
 void* cvmx_usb_read_csr32 (struct octeon_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_usb_schedule (struct octeon_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_usb_write_csr32 (struct octeon_hcd*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  octeon_usb_port_callback (struct octeon_hcd*) ; 
 int /*<<< orphan*/  prefetch_range (struct octeon_hcd*,int) ; 

__attribute__((used)) static int cvmx_usb_poll(struct octeon_hcd *usb)
{
	union cvmx_usbcx_hfnum usbc_hfnum;
	union cvmx_usbcx_gintsts usbc_gintsts;

	prefetch_range(usb, sizeof(*usb));

	/* Update the frame counter */
	usbc_hfnum.u32 = cvmx_usb_read_csr32(usb, CVMX_USBCX_HFNUM(usb->index));
	if ((usb->frame_number & 0x3fff) > usbc_hfnum.s.frnum)
		usb->frame_number += 0x4000;
	usb->frame_number &= ~0x3fffull;
	usb->frame_number |= usbc_hfnum.s.frnum;

	/* Read the pending interrupts */
	usbc_gintsts.u32 = cvmx_usb_read_csr32(usb,
					       CVMX_USBCX_GINTSTS(usb->index));

	/* Clear the interrupts now that we know about them */
	cvmx_usb_write_csr32(usb, CVMX_USBCX_GINTSTS(usb->index),
			     usbc_gintsts.u32);

	if (usbc_gintsts.s.rxflvl) {
		/*
		 * RxFIFO Non-Empty (RxFLvl)
		 * Indicates that there is at least one packet pending to be
		 * read from the RxFIFO.
		 *
		 * In DMA mode this is handled by hardware
		 */
		if (usb->init_flags & CVMX_USB_INITIALIZE_FLAGS_NO_DMA)
			cvmx_usb_poll_rx_fifo(usb);
	}
	if (usbc_gintsts.s.ptxfemp || usbc_gintsts.s.nptxfemp) {
		/* Fill the Tx FIFOs when not in DMA mode */
		if (usb->init_flags & CVMX_USB_INITIALIZE_FLAGS_NO_DMA)
			cvmx_usb_poll_tx_fifo(usb);
	}
	if (usbc_gintsts.s.disconnint || usbc_gintsts.s.prtint) {
		union cvmx_usbcx_hprt usbc_hprt;
		/*
		 * Disconnect Detected Interrupt (DisconnInt)
		 * Asserted when a device disconnect is detected.
		 *
		 * Host Port Interrupt (PrtInt)
		 * The core sets this bit to indicate a change in port status of
		 * one of the O2P USB core ports in Host mode. The application
		 * must read the Host Port Control and Status (HPRT) register to
		 * determine the exact event that caused this interrupt. The
		 * application must clear the appropriate status bit in the Host
		 * Port Control and Status register to clear this bit.
		 *
		 * Call the user's port callback
		 */
		octeon_usb_port_callback(usb);
		/* Clear the port change bits */
		usbc_hprt.u32 =
			cvmx_usb_read_csr32(usb, CVMX_USBCX_HPRT(usb->index));
		usbc_hprt.s.prtena = 0;
		cvmx_usb_write_csr32(usb, CVMX_USBCX_HPRT(usb->index),
				     usbc_hprt.u32);
	}
	if (usbc_gintsts.s.hchint) {
		/*
		 * Host Channels Interrupt (HChInt)
		 * The core sets this bit to indicate that an interrupt is
		 * pending on one of the channels of the core (in Host mode).
		 * The application must read the Host All Channels Interrupt
		 * (HAINT) register to determine the exact number of the channel
		 * on which the interrupt occurred, and then read the
		 * corresponding Host Channel-n Interrupt (HCINTn) register to
		 * determine the exact cause of the interrupt. The application
		 * must clear the appropriate status bit in the HCINTn register
		 * to clear this bit.
		 */
		union cvmx_usbcx_haint usbc_haint;

		usbc_haint.u32 = cvmx_usb_read_csr32(usb,
					CVMX_USBCX_HAINT(usb->index));
		while (usbc_haint.u32) {
			int channel;

			channel = __fls(usbc_haint.u32);
			cvmx_usb_poll_channel(usb, channel);
			usbc_haint.u32 ^= 1 << channel;
		}
	}

	cvmx_usb_schedule(usb, usbc_gintsts.s.sof);

	return 0;
}