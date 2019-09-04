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
typedef  int u8 ;
struct magicmouse_sc {int /*<<< orphan*/  input; int /*<<< orphan*/  quirks; int /*<<< orphan*/  scroll_accel; } ;
struct hid_report {int size; } ;
struct hid_device_id {scalar_t__ product; int /*<<< orphan*/  driver_data; } ;
struct hid_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  feature ;

/* Variables and functions */
 int /*<<< orphan*/  DOUBLE_REPORT_ID ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_CONNECT_DEFAULT ; 
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  HID_INPUT_REPORT ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 int /*<<< orphan*/  MOUSE_REPORT_ID ; 
 int /*<<< orphan*/  SCROLL_ACCEL_DEFAULT ; 
 int /*<<< orphan*/  TRACKPAD_REPORT_ID ; 
 scalar_t__ USB_DEVICE_ID_APPLE_MAGICMOUSE ; 
 struct magicmouse_sc* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*,...) ; 
 int hid_hw_raw_request (struct hid_device*,int,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hid_hw_start (struct hid_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int hid_parse (struct hid_device*) ; 
 struct hid_report* hid_register_report (struct hid_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_set_drvdata (struct hid_device*,struct magicmouse_sc*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmemdup (int const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int magicmouse_probe(struct hid_device *hdev,
	const struct hid_device_id *id)
{
	const u8 feature[] = { 0xd7, 0x01 };
	u8 *buf;
	struct magicmouse_sc *msc;
	struct hid_report *report;
	int ret;

	msc = devm_kzalloc(&hdev->dev, sizeof(*msc), GFP_KERNEL);
	if (msc == NULL) {
		hid_err(hdev, "can't alloc magicmouse descriptor\n");
		return -ENOMEM;
	}

	msc->scroll_accel = SCROLL_ACCEL_DEFAULT;

	msc->quirks = id->driver_data;
	hid_set_drvdata(hdev, msc);

	ret = hid_parse(hdev);
	if (ret) {
		hid_err(hdev, "magicmouse hid parse failed\n");
		return ret;
	}

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	if (ret) {
		hid_err(hdev, "magicmouse hw start failed\n");
		return ret;
	}

	if (!msc->input) {
		hid_err(hdev, "magicmouse input not registered\n");
		ret = -ENOMEM;
		goto err_stop_hw;
	}

	if (id->product == USB_DEVICE_ID_APPLE_MAGICMOUSE)
		report = hid_register_report(hdev, HID_INPUT_REPORT,
			MOUSE_REPORT_ID, 0);
	else { /* USB_DEVICE_ID_APPLE_MAGICTRACKPAD */
		report = hid_register_report(hdev, HID_INPUT_REPORT,
			TRACKPAD_REPORT_ID, 0);
		report = hid_register_report(hdev, HID_INPUT_REPORT,
			DOUBLE_REPORT_ID, 0);
	}

	if (!report) {
		hid_err(hdev, "unable to register touch report\n");
		ret = -ENOMEM;
		goto err_stop_hw;
	}
	report->size = 6;

	buf = kmemdup(feature, sizeof(feature), GFP_KERNEL);
	if (!buf) {
		ret = -ENOMEM;
		goto err_stop_hw;
	}

	/*
	 * Some devices repond with 'invalid report id' when feature
	 * report switching it into multitouch mode is sent to it.
	 *
	 * This results in -EIO from the _raw low-level transport callback,
	 * but there seems to be no other way of switching the mode.
	 * Thus the super-ugly hacky success check below.
	 */
	ret = hid_hw_raw_request(hdev, buf[0], buf, sizeof(feature),
				HID_FEATURE_REPORT, HID_REQ_SET_REPORT);
	kfree(buf);
	if (ret != -EIO && ret != sizeof(feature)) {
		hid_err(hdev, "unable to request touch data (%d)\n", ret);
		goto err_stop_hw;
	}

	return 0;
err_stop_hw:
	hid_hw_stop(hdev);
	return ret;
}