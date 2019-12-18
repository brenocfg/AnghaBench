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
struct usb_wwan_intf_private {int dummy; } ;
struct usb_serial {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct usb_wwan_intf_private*) ; 
 struct usb_wwan_intf_private* usb_get_serial_data (struct usb_serial*) ; 
 int /*<<< orphan*/  usb_set_serial_data (struct usb_serial*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qc_release(struct usb_serial *serial)
{
	struct usb_wwan_intf_private *priv = usb_get_serial_data(serial);

	usb_set_serial_data(serial, NULL);
	kfree(priv);
}