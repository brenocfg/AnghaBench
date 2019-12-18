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
struct hidpp_report {int report_id; int device_index; } ;
struct hidpp_device {int very_long_report_length; int quirks; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int HIDPP_QUIRK_FORCE_OUTPUT_REPORTS ; 
 int HIDPP_REPORT_LONG_LENGTH ; 
 int HIDPP_REPORT_SHORT_LENGTH ; 
 int /*<<< orphan*/  HID_OUTPUT_REPORT ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
#define  REPORT_ID_HIDPP_LONG 130 
#define  REPORT_ID_HIDPP_SHORT 129 
#define  REPORT_ID_HIDPP_VERY_LONG 128 
 struct hidpp_device* hid_get_drvdata (struct hid_device*) ; 
 int hid_hw_output_report (struct hid_device*,int /*<<< orphan*/ *,int) ; 
 int hid_hw_raw_request (struct hid_device*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __hidpp_send_report(struct hid_device *hdev,
				struct hidpp_report *hidpp_report)
{
	struct hidpp_device *hidpp = hid_get_drvdata(hdev);
	int fields_count, ret;

	switch (hidpp_report->report_id) {
	case REPORT_ID_HIDPP_SHORT:
		fields_count = HIDPP_REPORT_SHORT_LENGTH;
		break;
	case REPORT_ID_HIDPP_LONG:
		fields_count = HIDPP_REPORT_LONG_LENGTH;
		break;
	case REPORT_ID_HIDPP_VERY_LONG:
		fields_count = hidpp->very_long_report_length;
		break;
	default:
		return -ENODEV;
	}

	/*
	 * set the device_index as the receiver, it will be overwritten by
	 * hid_hw_request if needed
	 */
	hidpp_report->device_index = 0xff;

	if (hidpp->quirks & HIDPP_QUIRK_FORCE_OUTPUT_REPORTS) {
		ret = hid_hw_output_report(hdev, (u8 *)hidpp_report, fields_count);
	} else {
		ret = hid_hw_raw_request(hdev, hidpp_report->report_id,
			(u8 *)hidpp_report, fields_count, HID_OUTPUT_REPORT,
			HID_REQ_SET_REPORT);
	}

	return ret == fields_count ? 0 : -1;
}