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
struct usbhsg_uep {int dummy; } ;
struct usbhs_priv {int dummy; } ;
struct usb_ctrlrequest {int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; } ;

/* Variables and functions */
#define  USB_DEVICE_TEST_MODE 128 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usbhs_sys_set_test_mode (struct usbhs_priv*,int) ; 
 int /*<<< orphan*/  usbhsg_recip_handler_std_control_done (struct usbhs_priv*,struct usbhsg_uep*,struct usb_ctrlrequest*) ; 

__attribute__((used)) static int usbhsg_recip_handler_std_set_device(struct usbhs_priv *priv,
						 struct usbhsg_uep *uep,
						 struct usb_ctrlrequest *ctrl)
{
	switch (le16_to_cpu(ctrl->wValue)) {
	case USB_DEVICE_TEST_MODE:
		usbhsg_recip_handler_std_control_done(priv, uep, ctrl);
		udelay(100);
		usbhs_sys_set_test_mode(priv, le16_to_cpu(ctrl->wIndex) >> 8);
		break;
	default:
		usbhsg_recip_handler_std_control_done(priv, uep, ctrl);
		break;
	}

	return 0;
}