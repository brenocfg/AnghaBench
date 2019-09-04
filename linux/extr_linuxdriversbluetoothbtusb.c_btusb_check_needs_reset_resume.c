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
struct usb_interface {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_QUIRK_RESET_RESUME ; 
 int /*<<< orphan*/  btusb_needs_reset_resume_table ; 
 scalar_t__ dmi_check_system (int /*<<< orphan*/ ) ; 
 TYPE_1__* interface_to_usbdev (struct usb_interface*) ; 

__attribute__((used)) static void btusb_check_needs_reset_resume(struct usb_interface *intf)
{
	if (dmi_check_system(btusb_needs_reset_resume_table))
		interface_to_usbdev(intf)->quirks |= USB_QUIRK_RESET_RESUME;
}