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
typedef  int /*<<< orphan*/  u16 ;
struct usbhsh_hpriv {int dummy; } ;
struct usbhs_priv {int dummy; } ;
struct usb_hcd {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
#define  ClearHubFeature 134 
#define  ClearPortFeature 133 
 int EPIPE ; 
#define  GetHubDescriptor 132 
#define  GetHubStatus 131 
#define  GetPortStatus 130 
#define  SetHubFeature 129 
#define  SetPortFeature 128 
 int __usbhsh_hub_get_status (struct usbhsh_hpriv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int __usbhsh_hub_hub_feature (struct usbhsh_hpriv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int __usbhsh_hub_port_feature (struct usbhsh_hpriv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct device* usbhs_priv_to_dev (struct usbhs_priv*) ; 
 struct usbhsh_hpriv* usbhsh_hcd_to_hpriv (struct usb_hcd*) ; 
 struct usbhs_priv* usbhsh_hpriv_to_priv (struct usbhsh_hpriv*) ; 
 int /*<<< orphan*/  usbhsh_port_stat_get (struct usbhsh_hpriv*) ; 

__attribute__((used)) static int usbhsh_hub_control(struct usb_hcd *hcd, u16 typeReq, u16 wValue,
			      u16 wIndex, char *buf, u16 wLength)
{
	struct usbhsh_hpriv *hpriv = usbhsh_hcd_to_hpriv(hcd);
	struct usbhs_priv *priv = usbhsh_hpriv_to_priv(hpriv);
	struct device *dev = usbhs_priv_to_dev(priv);
	int ret = -EPIPE;

	switch (typeReq) {

	/* Hub Feature */
	case ClearHubFeature:
	case SetHubFeature:
		ret = __usbhsh_hub_hub_feature(hpriv, typeReq,
					       wValue, wIndex, buf, wLength);
		break;

	/* Port Feature */
	case SetPortFeature:
	case ClearPortFeature:
		ret = __usbhsh_hub_port_feature(hpriv, typeReq,
						wValue, wIndex, buf, wLength);
		break;

	/* Get status */
	case GetHubStatus:
	case GetPortStatus:
	case GetHubDescriptor:
		ret = __usbhsh_hub_get_status(hpriv, typeReq,
					      wValue, wIndex, buf, wLength);
		break;
	}

	dev_dbg(dev, "typeReq = %x, ret = %d, port_stat = %x\n",
		typeReq, ret, usbhsh_port_stat_get(hpriv));

	return ret;
}