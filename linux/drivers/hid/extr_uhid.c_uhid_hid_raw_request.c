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
typedef  int /*<<< orphan*/  u8 ;
struct hid_device {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
#define  HID_FEATURE_REPORT 132 
#define  HID_INPUT_REPORT 131 
#define  HID_OUTPUT_REPORT 130 
#define  HID_REQ_GET_REPORT 129 
#define  HID_REQ_SET_REPORT 128 
 int /*<<< orphan*/  UHID_FEATURE_REPORT ; 
 int /*<<< orphan*/  UHID_INPUT_REPORT ; 
 int /*<<< orphan*/  UHID_OUTPUT_REPORT ; 
 int uhid_hid_get_report (struct hid_device*,unsigned char,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int uhid_hid_set_report (struct hid_device*,unsigned char,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uhid_hid_raw_request(struct hid_device *hid, unsigned char reportnum,
				__u8 *buf, size_t len, unsigned char rtype,
				int reqtype)
{
	u8 u_rtype;

	switch (rtype) {
	case HID_FEATURE_REPORT:
		u_rtype = UHID_FEATURE_REPORT;
		break;
	case HID_OUTPUT_REPORT:
		u_rtype = UHID_OUTPUT_REPORT;
		break;
	case HID_INPUT_REPORT:
		u_rtype = UHID_INPUT_REPORT;
		break;
	default:
		return -EINVAL;
	}

	switch (reqtype) {
	case HID_REQ_GET_REPORT:
		return uhid_hid_get_report(hid, reportnum, buf, len, u_rtype);
	case HID_REQ_SET_REPORT:
		return uhid_hid_set_report(hid, reportnum, buf, len, u_rtype);
	default:
		return -EIO;
	}
}