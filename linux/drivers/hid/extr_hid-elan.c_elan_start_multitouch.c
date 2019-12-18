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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*,int) ; 
 int hid_hw_raw_request (struct hid_device*,unsigned char,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmemdup (unsigned char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int elan_start_multitouch(struct hid_device *hdev)
{
	int ret;

	/*
	 * This byte sequence will enable multitouch mode and disable
	 * mouse emulation
	 */
	static const unsigned char buf[] = { 0x0D, 0x00, 0x03, 0x21, 0x00 };
	unsigned char *dmabuf = kmemdup(buf, sizeof(buf), GFP_KERNEL);

	if (!dmabuf)
		return -ENOMEM;

	ret = hid_hw_raw_request(hdev, dmabuf[0], dmabuf, sizeof(buf),
				 HID_FEATURE_REPORT, HID_REQ_SET_REPORT);

	kfree(dmabuf);

	if (ret != sizeof(buf)) {
		hid_err(hdev, "Failed to start multitouch: %d\n", ret);
		return ret;
	}

	return 0;
}