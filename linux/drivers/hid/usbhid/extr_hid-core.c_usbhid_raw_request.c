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
struct hid_device {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int EIO ; 
#define  HID_REQ_GET_REPORT 129 
#define  HID_REQ_SET_REPORT 128 
 int usbhid_get_raw_report (struct hid_device*,unsigned char,int /*<<< orphan*/ *,size_t,unsigned char) ; 
 int usbhid_set_raw_report (struct hid_device*,unsigned char,int /*<<< orphan*/ *,size_t,unsigned char) ; 

__attribute__((used)) static int usbhid_raw_request(struct hid_device *hid, unsigned char reportnum,
			      __u8 *buf, size_t len, unsigned char rtype,
			      int reqtype)
{
	switch (reqtype) {
	case HID_REQ_GET_REPORT:
		return usbhid_get_raw_report(hid, reportnum, buf, len, rtype);
	case HID_REQ_SET_REPORT:
		return usbhid_set_raw_report(hid, reportnum, buf, len, rtype);
	default:
		return -EIO;
	}
}