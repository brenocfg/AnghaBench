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
struct usbhsg_gpriv {int dummy; } ;
struct usbhs_priv {int dummy; } ;
struct usb_ctrlrequest {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBHSG_STATUS_SELF_POWERED ; 
 int USB_DEVICE_SELF_POWERED ; 
 int /*<<< orphan*/  __usbhsg_recip_send_status (struct usbhsg_gpriv*,unsigned short) ; 
 scalar_t__ usbhsg_status_has (struct usbhsg_gpriv*,int /*<<< orphan*/ ) ; 
 struct usbhsg_gpriv* usbhsg_uep_to_gpriv (struct usbhsg_uep*) ; 

__attribute__((used)) static int usbhsg_recip_handler_std_get_device(struct usbhs_priv *priv,
					       struct usbhsg_uep *uep,
					       struct usb_ctrlrequest *ctrl)
{
	struct usbhsg_gpriv *gpriv = usbhsg_uep_to_gpriv(uep);
	unsigned short status = 0;

	if (usbhsg_status_has(gpriv, USBHSG_STATUS_SELF_POWERED))
		status = 1 << USB_DEVICE_SELF_POWERED;

	__usbhsg_recip_send_status(gpriv, status);

	return 0;
}