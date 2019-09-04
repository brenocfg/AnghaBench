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
struct TYPE_4__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct usb_host_interface {TYPE_2__ desc; } ;
struct usb_cdc_line_coding {int bDataBits; int /*<<< orphan*/  dwDTERate; } ;
struct ims_pcu {int /*<<< orphan*/  dev; int /*<<< orphan*/  udev; scalar_t__ cmd_buf; TYPE_1__* ctrl_intf; } ;
struct TYPE_3__ {struct usb_host_interface* cur_altsetting; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_CDC_REQ_SET_CONTROL_LINE_STATE ; 
 int /*<<< orphan*/  USB_CDC_REQ_SET_LINE_CODING ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct usb_cdc_line_coding*,int /*<<< orphan*/ ,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct usb_cdc_line_coding*,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ims_pcu_line_setup(struct ims_pcu *pcu)
{
	struct usb_host_interface *interface = pcu->ctrl_intf->cur_altsetting;
	struct usb_cdc_line_coding *line = (void *)pcu->cmd_buf;
	int error;

	memset(line, 0, sizeof(*line));
	line->dwDTERate = cpu_to_le32(57600);
	line->bDataBits = 8;

	error = usb_control_msg(pcu->udev, usb_sndctrlpipe(pcu->udev, 0),
				USB_CDC_REQ_SET_LINE_CODING,
				USB_TYPE_CLASS | USB_RECIP_INTERFACE,
				0, interface->desc.bInterfaceNumber,
				line, sizeof(struct usb_cdc_line_coding),
				5000);
	if (error < 0) {
		dev_err(pcu->dev, "Failed to set line coding, error: %d\n",
			error);
		return error;
	}

	error = usb_control_msg(pcu->udev, usb_sndctrlpipe(pcu->udev, 0),
				USB_CDC_REQ_SET_CONTROL_LINE_STATE,
				USB_TYPE_CLASS | USB_RECIP_INTERFACE,
				0x03, interface->desc.bInterfaceNumber,
				NULL, 0, 5000);
	if (error < 0) {
		dev_err(pcu->dev, "Failed to set line state, error: %d\n",
			error);
		return error;
	}

	return 0;
}