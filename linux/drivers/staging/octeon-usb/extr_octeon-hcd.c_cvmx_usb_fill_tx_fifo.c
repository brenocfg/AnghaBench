#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int xfersize; } ;
union cvmx_usbcx_hctsizx {TYPE_4__ s; void* u32; } ;
struct TYPE_5__ {scalar_t__ compsplt; scalar_t__ spltena; } ;
union cvmx_usbcx_hcspltx {TYPE_1__ s; void* u32; } ;
struct TYPE_6__ {scalar_t__ epdir; scalar_t__ eptype; } ;
union cvmx_usbcx_hccharx {TYPE_2__ s; void* u32; } ;
struct cvmx_usb_tx_fifo {size_t head; TYPE_3__* entry; } ;
struct octeon_hcd {int /*<<< orphan*/  index; struct cvmx_usb_tx_fifo nonperiodic; struct cvmx_usb_tx_fifo periodic; } ;
struct TYPE_7__ {int channel; int size; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_USBCX_HCCHARX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_USBCX_HCSPLTX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_USBCX_HCTSIZX (int,int /*<<< orphan*/ ) ; 
 scalar_t__ CVMX_USBNX_DMA0_OUTB_CHN0 (int /*<<< orphan*/ ) ; 
 scalar_t__ CVMX_USB_DIRECTION_OUT ; 
 scalar_t__ CVMX_USB_TRANSFER_INTERRUPT ; 
 scalar_t__ CVMX_USB_TRANSFER_ISOCHRONOUS ; 
 size_t MAX_CHANNELS ; 
 int /*<<< orphan*/  cvmx_read64_uint64 (scalar_t__) ; 
 int /*<<< orphan*/  cvmx_usb_poll_tx_fifo (struct octeon_hcd*) ; 
 void* cvmx_usb_read_csr32 (struct octeon_hcd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cvmx_usb_fill_tx_fifo(struct octeon_hcd *usb, int channel)
{
	union cvmx_usbcx_hccharx hcchar;
	union cvmx_usbcx_hcspltx usbc_hcsplt;
	union cvmx_usbcx_hctsizx usbc_hctsiz;
	struct cvmx_usb_tx_fifo *fifo;

	/* We only need to fill data on outbound channels */
	hcchar.u32 = cvmx_usb_read_csr32(usb,
			CVMX_USBCX_HCCHARX(channel, usb->index));
	if (hcchar.s.epdir != CVMX_USB_DIRECTION_OUT)
		return;

	/* OUT Splits only have data on the start and not the complete */
	usbc_hcsplt.u32 = cvmx_usb_read_csr32(usb,
				CVMX_USBCX_HCSPLTX(channel, usb->index));
	if (usbc_hcsplt.s.spltena && usbc_hcsplt.s.compsplt)
		return;

	/*
	 * Find out how many bytes we need to fill and convert it into 32bit
	 * words.
	 */
	usbc_hctsiz.u32 = cvmx_usb_read_csr32(usb,
				CVMX_USBCX_HCTSIZX(channel, usb->index));
	if (!usbc_hctsiz.s.xfersize)
		return;

	if ((hcchar.s.eptype == CVMX_USB_TRANSFER_INTERRUPT) ||
	    (hcchar.s.eptype == CVMX_USB_TRANSFER_ISOCHRONOUS))
		fifo = &usb->periodic;
	else
		fifo = &usb->nonperiodic;

	fifo->entry[fifo->head].channel = channel;
	fifo->entry[fifo->head].address =
		cvmx_read64_uint64(CVMX_USBNX_DMA0_OUTB_CHN0(usb->index) +
				   channel * 8);
	fifo->entry[fifo->head].size = (usbc_hctsiz.s.xfersize + 3) >> 2;
	fifo->head++;
	if (fifo->head > MAX_CHANNELS)
		fifo->head = 0;

	cvmx_usb_poll_tx_fifo(usb);
}