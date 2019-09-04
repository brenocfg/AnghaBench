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
typedef  int /*<<< orphan*/  const u8 ;
typedef  int /*<<< orphan*/  txbuf ;
struct hid_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 int /*<<< orphan*/  const RMI_SET_RMI_MODE_REPORT_ID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const,int) ; 
 int hid_hw_raw_request (struct hid_device*,int /*<<< orphan*/  const,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* kmemdup (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rmi_set_mode(struct hid_device *hdev, u8 mode)
{
	int ret;
	const u8 txbuf[2] = {RMI_SET_RMI_MODE_REPORT_ID, mode};
	u8 *buf;

	buf = kmemdup(txbuf, sizeof(txbuf), GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	ret = hid_hw_raw_request(hdev, RMI_SET_RMI_MODE_REPORT_ID, buf,
			sizeof(txbuf), HID_FEATURE_REPORT, HID_REQ_SET_REPORT);
	kfree(buf);
	if (ret < 0) {
		dev_err(&hdev->dev, "unable to set rmi mode to %d (%d)\n", mode,
			ret);
		return ret;
	}

	return 0;
}