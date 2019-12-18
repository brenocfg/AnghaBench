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
struct rmi_data {int device_flags; } ;
struct hid_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_OUTPUT_REPORT ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 int RMI_DEVICE_OUTPUT_SET_REPORT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct rmi_data* hid_get_drvdata (struct hid_device*) ; 
 int hid_hw_output_report (struct hid_device*,void*,int) ; 
 int hid_hw_raw_request (struct hid_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rmi_write_report(struct hid_device *hdev, u8 *report, int len)
{
	struct rmi_data *data = hid_get_drvdata(hdev);
	int ret;

	if (data->device_flags & RMI_DEVICE_OUTPUT_SET_REPORT) {
		/*
		 * Talk to device by using SET_REPORT requests instead.
		 */
		ret = hid_hw_raw_request(hdev, report[0], report,
				len, HID_OUTPUT_REPORT, HID_REQ_SET_REPORT);
	} else {
		ret = hid_hw_output_report(hdev, (void *)report, len);
	}

	if (ret < 0) {
		dev_err(&hdev->dev, "failed to write hid report (%d)\n", ret);
		return ret;
	}

	return ret;
}