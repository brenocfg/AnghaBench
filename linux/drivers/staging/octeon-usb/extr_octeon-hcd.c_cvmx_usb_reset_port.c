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
struct TYPE_2__ {void* u32; } ;
struct octeon_hcd {int /*<<< orphan*/  index; TYPE_1__ usbcx_hprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_USBCX_HPRT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_SET_FIELD32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* cvmx_usb_read_csr32 (struct octeon_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_usbcx_hprt ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  prtrst ; 

__attribute__((used)) static void cvmx_usb_reset_port(struct octeon_hcd *usb)
{
	usb->usbcx_hprt.u32 = cvmx_usb_read_csr32(usb,
						  CVMX_USBCX_HPRT(usb->index));

	/* Program the port reset bit to start the reset process */
	USB_SET_FIELD32(CVMX_USBCX_HPRT(usb->index), cvmx_usbcx_hprt,
			prtrst, 1);

	/*
	 * Wait at least 50ms (high speed), or 10ms (full speed) for the reset
	 * process to complete.
	 */
	mdelay(50);

	/* Program the port reset bit to 0, USBC_HPRT[PRTRST] = 0 */
	USB_SET_FIELD32(CVMX_USBCX_HPRT(usb->index), cvmx_usbcx_hprt,
			prtrst, 0);

	/*
	 * Read the port speed field to get the enumerated speed,
	 * USBC_HPRT[PRTSPD].
	 */
	usb->usbcx_hprt.u32 = cvmx_usb_read_csr32(usb,
						  CVMX_USBCX_HPRT(usb->index));
}