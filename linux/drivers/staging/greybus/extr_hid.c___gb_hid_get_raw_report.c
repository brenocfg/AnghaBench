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
struct hid_device {struct gb_hid* driver_data; } ;
struct gb_hid {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int EINVAL ; 
 unsigned char HID_OUTPUT_REPORT ; 
 int gb_hid_get_report (struct gb_hid*,unsigned char,unsigned char,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int __gb_hid_get_raw_report(struct hid_device *hid,
		unsigned char report_number, __u8 *buf, size_t count,
		unsigned char report_type)
{
	struct gb_hid *ghid = hid->driver_data;
	int ret;

	if (report_type == HID_OUTPUT_REPORT)
		return -EINVAL;

	ret = gb_hid_get_report(ghid, report_type, report_number, buf, count);
	if (!ret)
		ret = count;

	return ret;
}