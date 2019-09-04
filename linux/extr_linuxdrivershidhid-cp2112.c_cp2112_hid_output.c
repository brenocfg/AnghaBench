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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned char HID_OUTPUT_REPORT ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 int hid_hw_output_report (struct hid_device*,int /*<<< orphan*/ *,size_t) ; 
 int hid_hw_raw_request (struct hid_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cp2112_hid_output(struct hid_device *hdev, u8 *data, size_t count,
			     unsigned char report_type)
{
	u8 *buf;
	int ret;

	buf = kmemdup(data, count, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	if (report_type == HID_OUTPUT_REPORT)
		ret = hid_hw_output_report(hdev, buf, count);
	else
		ret = hid_hw_raw_request(hdev, buf[0], buf, count, report_type,
				HID_REQ_SET_REPORT);

	kfree(buf);
	return ret;
}