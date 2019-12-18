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
 int /*<<< orphan*/  mcs7830_apply_base_config (struct usbnet*) ; 
 struct usbnet* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usbnet_resume (struct usb_interface*) ; 

__attribute__((used)) static int mcs7830_reset_resume (struct usb_interface *intf)
{
 	/* YES, this function is successful enough that ethtool -d
           does show same output pre-/post-suspend */

	struct usbnet		*dev = usb_get_intfdata(intf);

	mcs7830_apply_base_config(dev);

	usbnet_resume(intf);

	return 0;
}