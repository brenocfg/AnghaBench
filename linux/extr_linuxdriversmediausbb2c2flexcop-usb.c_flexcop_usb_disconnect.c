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
struct usb_interface {int dummy; } ;
struct flexcop_usb {int /*<<< orphan*/  fc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  flexcop_device_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flexcop_device_kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flexcop_usb_exit (struct flexcop_usb*) ; 
 int /*<<< orphan*/  flexcop_usb_transfer_exit (struct flexcop_usb*) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 struct flexcop_usb* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static void flexcop_usb_disconnect(struct usb_interface *intf)
{
	struct flexcop_usb *fc_usb = usb_get_intfdata(intf);
	flexcop_usb_transfer_exit(fc_usb);
	flexcop_device_exit(fc_usb->fc_dev);
	flexcop_usb_exit(fc_usb);
	flexcop_device_kfree(fc_usb->fc_dev);
	info("%s successfully deinitialized and disconnected.", DRIVER_NAME);
}