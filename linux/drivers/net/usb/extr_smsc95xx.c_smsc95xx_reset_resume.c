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
struct usbnet {int dummy; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 int smsc95xx_reset (struct usbnet*) ; 
 int smsc95xx_resume (struct usb_interface*) ; 
 struct usbnet* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int smsc95xx_reset_resume(struct usb_interface *intf)
{
	struct usbnet *dev = usb_get_intfdata(intf);
	int ret;

	ret = smsc95xx_reset(dev);
	if (ret < 0)
		return ret;

	return smsc95xx_resume(intf);
}