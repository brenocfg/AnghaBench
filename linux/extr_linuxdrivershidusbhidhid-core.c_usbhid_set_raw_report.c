#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usbhid_device {struct usb_interface* intf; } ;
struct usb_interface {struct usb_host_interface* cur_altsetting; } ;
struct TYPE_2__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct usb_host_interface {TYPE_1__ desc; } ;
struct usb_device {int dummy; } ;
struct hid_device {int quirks; struct usbhid_device* driver_data; } ;
typedef  int __u8 ;

/* Variables and functions */
 unsigned char HID_OUTPUT_REPORT ; 
 int HID_QUIRK_SKIP_OUTPUT_REPORT_ID ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 struct usb_device* hid_to_usb_dev (struct hid_device*) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char,int /*<<< orphan*/ ,int*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbhid_set_raw_report(struct hid_device *hid, unsigned int reportnum,
				 __u8 *buf, size_t count, unsigned char rtype)
{
	struct usbhid_device *usbhid = hid->driver_data;
	struct usb_device *dev = hid_to_usb_dev(hid);
	struct usb_interface *intf = usbhid->intf;
	struct usb_host_interface *interface = intf->cur_altsetting;
	int ret, skipped_report_id = 0;

	/* Byte 0 is the report number. Report data starts at byte 1.*/
	if ((rtype == HID_OUTPUT_REPORT) &&
	    (hid->quirks & HID_QUIRK_SKIP_OUTPUT_REPORT_ID))
		buf[0] = 0;
	else
		buf[0] = reportnum;

	if (buf[0] == 0x0) {
		/* Don't send the Report ID */
		buf++;
		count--;
		skipped_report_id = 1;
	}

	ret = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			HID_REQ_SET_REPORT,
			USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			((rtype + 1) << 8) | reportnum,
			interface->desc.bInterfaceNumber, buf, count,
			USB_CTRL_SET_TIMEOUT);
	/* count also the report id, if this was a numbered report. */
	if (ret > 0 && skipped_report_id)
		ret++;

	return ret;
}