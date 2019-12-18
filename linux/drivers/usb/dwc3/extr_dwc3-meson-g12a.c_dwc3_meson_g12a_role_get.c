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
struct dwc3_meson_g12a {scalar_t__ otg_phy_mode; } ;
struct device {int dummy; } ;
typedef  enum usb_role { ____Placeholder_usb_role } usb_role ;

/* Variables and functions */
 scalar_t__ PHY_MODE_USB_HOST ; 
 int USB_ROLE_DEVICE ; 
 int USB_ROLE_HOST ; 
 struct dwc3_meson_g12a* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static enum usb_role dwc3_meson_g12a_role_get(struct device *dev)
{
	struct dwc3_meson_g12a *priv = dev_get_drvdata(dev);

	return priv->otg_phy_mode == PHY_MODE_USB_HOST ?
		USB_ROLE_HOST : USB_ROLE_DEVICE;
}