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
struct dvb_usb_device {struct dvb_usb_adapter* adapter; } ;
struct dvb_usb_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  az6007_ci_init (struct dvb_usb_adapter*) ; 
 int dvb_usbv2_resume (struct usb_interface*) ; 
 struct dvb_usb_device* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int az6007_resume(struct usb_interface *intf)
{
	struct dvb_usb_device *d = usb_get_intfdata(intf);
	struct dvb_usb_adapter *adap = &d->adapter[0];

	az6007_ci_init(adap);
	return dvb_usbv2_resume(intf);
}