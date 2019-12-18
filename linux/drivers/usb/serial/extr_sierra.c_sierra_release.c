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
struct usb_serial {int dummy; } ;
struct sierra_intf_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sierra_intf_private*) ; 
 struct sierra_intf_private* usb_get_serial_data (struct usb_serial*) ; 

__attribute__((used)) static void sierra_release(struct usb_serial *serial)
{
	struct sierra_intf_private *intfdata;

	intfdata = usb_get_serial_data(serial);
	kfree(intfdata);
}