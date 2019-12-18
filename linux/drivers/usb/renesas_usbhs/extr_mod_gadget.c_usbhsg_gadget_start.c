#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct usbhsg_gpriv {struct usb_gadget_driver* driver; TYPE_1__ gadget; TYPE_2__* transceiver; } ;
struct usbhs_priv {int dummy; } ;
struct usb_gadget_driver {scalar_t__ max_speed; int /*<<< orphan*/  setup; } ;
struct usb_gadget {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  otg; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (TYPE_2__*) ; 
 int /*<<< orphan*/  USBHSG_STATUS_REGISTERD ; 
 scalar_t__ USB_SPEED_FULL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int otg_set_peripheral (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  usbhs_mod_phy_mode (struct usbhs_priv*) ; 
 struct device* usbhs_priv_to_dev (struct usbhs_priv*) ; 
 struct usbhsg_gpriv* usbhsg_gadget_to_gpriv (struct usb_gadget*) ; 
 struct usbhs_priv* usbhsg_gpriv_to_priv (struct usbhsg_gpriv*) ; 
 int usbhsg_try_start (struct usbhs_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbhsg_gadget_start(struct usb_gadget *gadget,
		struct usb_gadget_driver *driver)
{
	struct usbhsg_gpriv *gpriv = usbhsg_gadget_to_gpriv(gadget);
	struct usbhs_priv *priv = usbhsg_gpriv_to_priv(gpriv);
	struct device *dev = usbhs_priv_to_dev(priv);
	int ret;

	if (!driver		||
	    !driver->setup	||
	    driver->max_speed < USB_SPEED_FULL)
		return -EINVAL;

	/* connect to bus through transceiver */
	if (!IS_ERR_OR_NULL(gpriv->transceiver)) {
		ret = otg_set_peripheral(gpriv->transceiver->otg,
					&gpriv->gadget);
		if (ret) {
			dev_err(dev, "%s: can't bind to transceiver\n",
				gpriv->gadget.name);
			return ret;
		}

		/* get vbus using phy versions */
		usbhs_mod_phy_mode(priv);
	}

	/* first hook up the driver ... */
	gpriv->driver = driver;

	return usbhsg_try_start(priv, USBHSG_STATUS_REGISTERD);
}