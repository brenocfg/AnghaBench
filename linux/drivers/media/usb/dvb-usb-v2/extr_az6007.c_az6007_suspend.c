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
struct dvb_usb_device {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  az6007_ci_uninit (struct dvb_usb_device*) ; 
 int dvb_usbv2_suspend (struct usb_interface*,int /*<<< orphan*/ ) ; 
 struct dvb_usb_device* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int az6007_suspend(struct usb_interface *intf, pm_message_t msg)
{
	struct dvb_usb_device *d = usb_get_intfdata(intf);

	az6007_ci_uninit(d);
	return dvb_usbv2_suspend(intf, msg);
}