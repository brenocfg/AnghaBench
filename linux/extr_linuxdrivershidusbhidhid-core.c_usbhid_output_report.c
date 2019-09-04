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
struct usbhid_device {TYPE_1__* urbout; } ;
struct usb_device {int dummy; } ;
struct hid_device {struct usbhid_device* driver_data; } ;
typedef  int __u8 ;
struct TYPE_2__ {int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 struct usb_device* hid_to_usb_dev (struct hid_device*) ; 
 int usb_interrupt_msg (struct usb_device*,int /*<<< orphan*/ ,int*,size_t,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbhid_output_report(struct hid_device *hid, __u8 *buf, size_t count)
{
	struct usbhid_device *usbhid = hid->driver_data;
	struct usb_device *dev = hid_to_usb_dev(hid);
	int actual_length, skipped_report_id = 0, ret;

	if (!usbhid->urbout)
		return -ENOSYS;

	if (buf[0] == 0x0) {
		/* Don't send the Report ID */
		buf++;
		count--;
		skipped_report_id = 1;
	}

	ret = usb_interrupt_msg(dev, usbhid->urbout->pipe,
				buf, count, &actual_length,
				USB_CTRL_SET_TIMEOUT);
	/* return the number of bytes transferred */
	if (ret == 0) {
		ret = actual_length;
		/* count also the report id */
		if (skipped_report_id)
			ret++;
	}

	return ret;
}