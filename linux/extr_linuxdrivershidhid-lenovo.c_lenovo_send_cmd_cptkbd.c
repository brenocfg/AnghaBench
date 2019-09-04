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
struct hid_device {int product; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
#define  USB_DEVICE_ID_LENOVO_CBTKBD 129 
#define  USB_DEVICE_ID_LENOVO_CUSBKBD 128 
 int hid_hw_output_report (struct hid_device*,unsigned char*,int) ; 
 int hid_hw_raw_request (struct hid_device*,int,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lenovo_send_cmd_cptkbd(struct hid_device *hdev,
			unsigned char byte2, unsigned char byte3)
{
	int ret;
	unsigned char *buf;

	buf = kzalloc(3, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	buf[0] = 0x18;
	buf[1] = byte2;
	buf[2] = byte3;

	switch (hdev->product) {
	case USB_DEVICE_ID_LENOVO_CUSBKBD:
		ret = hid_hw_raw_request(hdev, 0x13, buf, 3,
					HID_FEATURE_REPORT, HID_REQ_SET_REPORT);
		break;
	case USB_DEVICE_ID_LENOVO_CBTKBD:
		ret = hid_hw_output_report(hdev, buf, 3);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	kfree(buf);

	return ret < 0 ? ret : 0; /* BT returns 0, USB returns sizeof(buf) */
}