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
struct net_device {int dummy; } ;
struct gs_identify_mode {int /*<<< orphan*/  mode; } ;
struct gs_can {int /*<<< orphan*/  channel; int /*<<< orphan*/  iface; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GS_CAN_IDENTIFY_OFF ; 
 int /*<<< orphan*/  GS_CAN_IDENTIFY_ON ; 
 int /*<<< orphan*/  GS_USB_BREQ_IDENTIFY ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  interface_to_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gs_identify_mode*) ; 
 struct gs_identify_mode* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct gs_can* netdev_priv (struct net_device*) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gs_identify_mode*,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gs_usb_set_identify(struct net_device *netdev, bool do_identify)
{
	struct gs_can *dev = netdev_priv(netdev);
	struct gs_identify_mode *imode;
	int rc;

	imode = kmalloc(sizeof(*imode), GFP_KERNEL);

	if (!imode)
		return -ENOMEM;

	if (do_identify)
		imode->mode = GS_CAN_IDENTIFY_ON;
	else
		imode->mode = GS_CAN_IDENTIFY_OFF;

	rc = usb_control_msg(interface_to_usbdev(dev->iface),
			     usb_sndctrlpipe(interface_to_usbdev(dev->iface),
					     0),
			     GS_USB_BREQ_IDENTIFY,
			     USB_DIR_OUT | USB_TYPE_VENDOR |
			     USB_RECIP_INTERFACE,
			     dev->channel,
			     0,
			     imode,
			     sizeof(*imode),
			     100);

	kfree(imode);

	return (rc > 0) ? 0 : rc;
}