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
struct TYPE_5__ {int ptxfsize; int ptxfstaddr; } ;
union cvmx_usbcx_hptxfsiz {void* u32; TYPE_2__ s; } ;
struct TYPE_4__ {int nptxfdep; int nptxfstaddr; } ;
union cvmx_usbcx_gnptxfsiz {void* u32; TYPE_1__ s; } ;
struct TYPE_6__ {int dfifodepth; } ;
union cvmx_usbcx_ghwcfg3 {TYPE_3__ s; void* u32; } ;
struct octeon_hcd {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_USBCX_GHWCFG3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_USBCX_GNPTXFSIZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_USBCX_GRSTCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_USBCX_GRXFSIZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_USBCX_HPTXFSIZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_SET_FIELD32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* cvmx_usb_read_csr32 (struct octeon_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_usb_write_csr32 (struct octeon_hcd*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  cvmx_usbcx_grstctl ; 
 int /*<<< orphan*/  cvmx_usbcx_grxfsiz ; 
 int /*<<< orphan*/  cvmx_wait_tx_rx (struct octeon_hcd*,int) ; 
 int /*<<< orphan*/  rxfdep ; 
 int /*<<< orphan*/  rxfflsh ; 
 int /*<<< orphan*/  txfflsh ; 
 int /*<<< orphan*/  txfnum ; 

__attribute__((used)) static void cvmx_fifo_setup(struct octeon_hcd *usb)
{
	union cvmx_usbcx_ghwcfg3 usbcx_ghwcfg3;
	union cvmx_usbcx_gnptxfsiz npsiz;
	union cvmx_usbcx_hptxfsiz psiz;

	usbcx_ghwcfg3.u32 = cvmx_usb_read_csr32(usb,
						CVMX_USBCX_GHWCFG3(usb->index));

	/*
	 * Program the USBC_GRXFSIZ register to select the size of the receive
	 * FIFO (25%).
	 */
	USB_SET_FIELD32(CVMX_USBCX_GRXFSIZ(usb->index), cvmx_usbcx_grxfsiz,
			rxfdep, usbcx_ghwcfg3.s.dfifodepth / 4);

	/*
	 * Program the USBC_GNPTXFSIZ register to select the size and the start
	 * address of the non-periodic transmit FIFO for nonperiodic
	 * transactions (50%).
	 */
	npsiz.u32 = cvmx_usb_read_csr32(usb, CVMX_USBCX_GNPTXFSIZ(usb->index));
	npsiz.s.nptxfdep = usbcx_ghwcfg3.s.dfifodepth / 2;
	npsiz.s.nptxfstaddr = usbcx_ghwcfg3.s.dfifodepth / 4;
	cvmx_usb_write_csr32(usb, CVMX_USBCX_GNPTXFSIZ(usb->index), npsiz.u32);

	/*
	 * Program the USBC_HPTXFSIZ register to select the size and start
	 * address of the periodic transmit FIFO for periodic transactions
	 * (25%).
	 */
	psiz.u32 = cvmx_usb_read_csr32(usb, CVMX_USBCX_HPTXFSIZ(usb->index));
	psiz.s.ptxfsize = usbcx_ghwcfg3.s.dfifodepth / 4;
	psiz.s.ptxfstaddr = 3 * usbcx_ghwcfg3.s.dfifodepth / 4;
	cvmx_usb_write_csr32(usb, CVMX_USBCX_HPTXFSIZ(usb->index), psiz.u32);

	/* Flush all FIFOs */
	USB_SET_FIELD32(CVMX_USBCX_GRSTCTL(usb->index),
			cvmx_usbcx_grstctl, txfnum, 0x10);
	USB_SET_FIELD32(CVMX_USBCX_GRSTCTL(usb->index),
			cvmx_usbcx_grstctl, txfflsh, 1);
	cvmx_wait_tx_rx(usb, 0);
	USB_SET_FIELD32(CVMX_USBCX_GRSTCTL(usb->index),
			cvmx_usbcx_grstctl, rxfflsh, 1);
	cvmx_wait_tx_rx(usb, 1);
}