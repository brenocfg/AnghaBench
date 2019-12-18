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
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/ * DeviceRemovable; } ;
struct TYPE_4__ {TYPE_1__ hs; } ;
struct usb_hub_descriptor {int bPwrOn2PwrGood; int bNbrPorts; int bDescLength; int /*<<< orphan*/  wHubCharacteristics; TYPE_2__ u; scalar_t__ bHubContrCurrent; int /*<<< orphan*/  bDescriptorType; } ;
struct isp1760_hcd {int /*<<< orphan*/  hcs_params; } ;

/* Variables and functions */
 int HCS_N_PORTS (int /*<<< orphan*/ ) ; 
 scalar_t__ HCS_PPC (int /*<<< orphan*/ ) ; 
 int HUB_CHAR_INDV_PORT_LPSM ; 
 int HUB_CHAR_INDV_PORT_OCPM ; 
 int HUB_CHAR_NO_LPSM ; 
 int /*<<< orphan*/  USB_DT_HUB ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void isp1760_hub_descriptor(struct isp1760_hcd *priv,
		struct usb_hub_descriptor *desc)
{
	int ports = HCS_N_PORTS(priv->hcs_params);
	u16 temp;

	desc->bDescriptorType = USB_DT_HUB;
	/* priv 1.0, 2.3.9 says 20ms max */
	desc->bPwrOn2PwrGood = 10;
	desc->bHubContrCurrent = 0;

	desc->bNbrPorts = ports;
	temp = 1 + (ports / 8);
	desc->bDescLength = 7 + 2 * temp;

	/* ports removable, and usb 1.0 legacy PortPwrCtrlMask */
	memset(&desc->u.hs.DeviceRemovable[0], 0, temp);
	memset(&desc->u.hs.DeviceRemovable[temp], 0xff, temp);

	/* per-port overcurrent reporting */
	temp = HUB_CHAR_INDV_PORT_OCPM;
	if (HCS_PPC(priv->hcs_params))
		/* per-port power control */
		temp |= HUB_CHAR_INDV_PORT_LPSM;
	else
		/* no power switching */
		temp |= HUB_CHAR_NO_LPSM;
	desc->wHubCharacteristics = cpu_to_le16(temp);
}