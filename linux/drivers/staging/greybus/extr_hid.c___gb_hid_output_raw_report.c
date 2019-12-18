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
typedef  int __u8 ;

/* Variables and functions */
 int EINVAL ; 
 unsigned char HID_INPUT_REPORT ; 
 int gb_hid_set_report (struct gb_hid*,unsigned char,int,int*,size_t) ; 

__attribute__((used)) static int __gb_hid_output_raw_report(struct hid_device *hid, __u8 *buf,
				      size_t len, unsigned char report_type)
{
	struct gb_hid *ghid = hid->driver_data;
	int report_id = buf[0];
	int ret;

	if (report_type == HID_INPUT_REPORT)
		return -EINVAL;

	if (report_id) {
		buf++;
		len--;
	}

	ret = gb_hid_set_report(ghid, report_type, report_id, buf, len);
	if (report_id && ret >= 0)
		ret++; /* add report_id to the number of transfered bytes */

	return 0;
}