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
struct renesas_usb3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB3_AXI_INT_ENA ; 
 int /*<<< orphan*/  USB3_P0_INT_ENA ; 
 int /*<<< orphan*/  USB3_USB_INT_ENA_1 ; 
 int /*<<< orphan*/  USB3_USB_INT_ENA_2 ; 
 int /*<<< orphan*/  USB3_USB_OTG_INT_ENA ; 
 int /*<<< orphan*/  usb3_disconnect (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_write (struct renesas_usb3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void renesas_usb3_stop_controller(struct renesas_usb3 *usb3)
{
	usb3_disconnect(usb3);
	usb3_write(usb3, 0, USB3_P0_INT_ENA);
	usb3_write(usb3, 0, USB3_USB_OTG_INT_ENA);
	usb3_write(usb3, 0, USB3_USB_INT_ENA_1);
	usb3_write(usb3, 0, USB3_USB_INT_ENA_2);
	usb3_write(usb3, 0, USB3_AXI_INT_ENA);
}