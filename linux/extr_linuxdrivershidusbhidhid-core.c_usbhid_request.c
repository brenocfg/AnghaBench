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
struct hid_report {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
#define  HID_REQ_GET_REPORT 129 
#define  HID_REQ_SET_REPORT 128 
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  USB_DIR_OUT ; 
 int /*<<< orphan*/  usbhid_submit_report (struct hid_device*,struct hid_report*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usbhid_request(struct hid_device *hid, struct hid_report *rep, int reqtype)
{
	switch (reqtype) {
	case HID_REQ_GET_REPORT:
		usbhid_submit_report(hid, rep, USB_DIR_IN);
		break;
	case HID_REQ_SET_REPORT:
		usbhid_submit_report(hid, rep, USB_DIR_OUT);
		break;
	}
}