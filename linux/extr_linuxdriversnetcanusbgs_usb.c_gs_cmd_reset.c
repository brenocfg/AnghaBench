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
struct gs_device_mode {int /*<<< orphan*/  mode; } ;
struct gs_can {int /*<<< orphan*/  channel; struct usb_interface* iface; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GS_CAN_MODE_RESET ; 
 int /*<<< orphan*/  GS_USB_BREQ_MODE ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct gs_device_mode*) ; 
 struct gs_device_mode* kzalloc (int,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gs_device_mode*,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gs_cmd_reset(struct gs_can *gsdev)
{
	struct gs_device_mode *dm;
	struct usb_interface *intf = gsdev->iface;
	int rc;

	dm = kzalloc(sizeof(*dm), GFP_KERNEL);
	if (!dm)
		return -ENOMEM;

	dm->mode = GS_CAN_MODE_RESET;

	rc = usb_control_msg(interface_to_usbdev(intf),
			     usb_sndctrlpipe(interface_to_usbdev(intf), 0),
			     GS_USB_BREQ_MODE,
			     USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			     gsdev->channel,
			     0,
			     dm,
			     sizeof(*dm),
			     1000);

	kfree(dm);

	return rc;
}