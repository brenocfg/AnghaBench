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
 int /*<<< orphan*/  HID_REQ_GET_REPORT ; 
 int hid_hw_raw_request (struct hid_device*,unsigned char,int /*<<< orphan*/ *,size_t,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int cp2112_hid_get(struct hid_device *hdev, unsigned char report_number,
			  u8 *data, size_t count, unsigned char report_type)
{
	u8 *buf;
	int ret;

	buf = kmalloc(count, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	ret = hid_hw_raw_request(hdev, report_number, buf, count,
				       report_type, HID_REQ_GET_REPORT);
	memcpy(data, buf, count);
	kfree(buf);
	return ret;
}