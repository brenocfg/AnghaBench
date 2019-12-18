#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct steam_device {TYPE_2__* hdev; } ;
struct hid_report {int dummy; } ;
struct TYPE_4__ {TYPE_1__* report_enum; } ;
struct TYPE_3__ {struct hid_report** report_id_hash; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  HID_REQ_GET_REPORT ; 
 int /*<<< orphan*/ * hid_alloc_report_buf (struct hid_report*,int /*<<< orphan*/ ) ; 
 int hid_hw_raw_request (TYPE_2__*,int,int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ ) ; 
 int hid_report_len (struct hid_report*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int) ; 

__attribute__((used)) static int steam_recv_report(struct steam_device *steam,
		u8 *data, int size)
{
	struct hid_report *r;
	u8 *buf;
	int ret;

	r = steam->hdev->report_enum[HID_FEATURE_REPORT].report_id_hash[0];
	if (hid_report_len(r) < 64)
		return -EINVAL;

	buf = hid_alloc_report_buf(r, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	/*
	 * The report ID is always 0, so strip the first byte from the output.
	 * hid_report_len() is not counting the report ID, so +1 to the length
	 * or else we get a EOVERFLOW. We are safe from a buffer overflow
	 * because hid_alloc_report_buf() allocates +7 bytes.
	 */
	ret = hid_hw_raw_request(steam->hdev, 0x00,
			buf, hid_report_len(r) + 1,
			HID_FEATURE_REPORT, HID_REQ_GET_REPORT);
	if (ret > 0)
		memcpy(data, buf + 1, min(size, ret - 1));
	kfree(buf);
	return ret;
}