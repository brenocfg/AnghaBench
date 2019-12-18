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
struct TYPE_2__ {int frnum; } ;
union cvmx_usbcx_hfnum {TYPE_1__ s; int /*<<< orphan*/  u32; } ;
struct octeon_hcd {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_USBCX_HFNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_usb_read_csr32 (struct octeon_hcd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cvmx_usb_get_frame_number(struct octeon_hcd *usb)
{
	union cvmx_usbcx_hfnum usbc_hfnum;

	usbc_hfnum.u32 = cvmx_usb_read_csr32(usb, CVMX_USBCX_HFNUM(usb->index));

	return usbc_hfnum.s.frnum;
}