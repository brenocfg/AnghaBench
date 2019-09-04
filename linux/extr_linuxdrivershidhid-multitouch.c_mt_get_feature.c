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
typedef  int /*<<< orphan*/  u32 ;
struct hid_report {int /*<<< orphan*/  id; } ;
struct hid_device {int quirks; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
 int HID_QUIRK_NO_INIT_REPORTS ; 
 int /*<<< orphan*/  HID_REQ_GET_REPORT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * hid_alloc_report_buf (struct hid_report*,int /*<<< orphan*/ ) ; 
 int hid_hw_raw_request (struct hid_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_report_len (struct hid_report*) ; 
 int hid_report_raw_event (struct hid_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt_get_feature(struct hid_device *hdev, struct hid_report *report)
{
	int ret;
	u32 size = hid_report_len(report);
	u8 *buf;

	/*
	 * Do not fetch the feature report if the device has been explicitly
	 * marked as non-capable.
	 */
	if (hdev->quirks & HID_QUIRK_NO_INIT_REPORTS)
		return;

	buf = hid_alloc_report_buf(report, GFP_KERNEL);
	if (!buf)
		return;

	ret = hid_hw_raw_request(hdev, report->id, buf, size,
				 HID_FEATURE_REPORT, HID_REQ_GET_REPORT);
	if (ret < 0) {
		dev_warn(&hdev->dev, "failed to fetch feature %d\n",
			 report->id);
	} else {
		ret = hid_report_raw_event(hdev, HID_FEATURE_REPORT, buf,
					   size, 0);
		if (ret)
			dev_warn(&hdev->dev, "failed to report feature\n");
	}

	kfree(buf);
}