#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct hid_report {int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct hid_device {TYPE_1__* ll_driver; } ;
struct TYPE_2__ {int (* raw_request ) (struct hid_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HID_REQ_GET_REPORT ; 
 int HID_REQ_SET_REPORT ; 
 int /*<<< orphan*/  dbg_hid (char*,int) ; 
 char* hid_alloc_report_buf (struct hid_report*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_input_report (struct hid_device*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_output_report (struct hid_report*,char*) ; 
 int /*<<< orphan*/  hid_report_len (struct hid_report*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int stub1 (struct hid_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int __hid_request(struct hid_device *hid, struct hid_report *report,
		int reqtype)
{
	char *buf;
	int ret;
	u32 len;

	buf = hid_alloc_report_buf(report, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	len = hid_report_len(report);

	if (reqtype == HID_REQ_SET_REPORT)
		hid_output_report(report, buf);

	ret = hid->ll_driver->raw_request(hid, report->id, buf, len,
					  report->type, reqtype);
	if (ret < 0) {
		dbg_hid("unable to complete request: %d\n", ret);
		goto out;
	}

	if (reqtype == HID_REQ_GET_REPORT)
		hid_input_report(hid, report->type, buf, ret, 0);

	ret = 0;

out:
	kfree(buf);
	return ret;
}