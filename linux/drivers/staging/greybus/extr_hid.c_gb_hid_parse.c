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
struct hid_device {struct gb_hid* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  wReportDescLength; } ;
struct gb_hid {TYPE_1__ hdesc; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int HID_MAX_DESCRIPTOR_SIZE ; 
 int /*<<< orphan*/  dbg_hid (char*,...) ; 
 int gb_hid_get_report_desc (struct gb_hid*,char*) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int hid_parse_report (struct hid_device*,char*,unsigned int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_hid_parse(struct hid_device *hid)
{
	struct gb_hid *ghid = hid->driver_data;
	unsigned int rsize;
	char *rdesc;
	int ret;

	rsize = le16_to_cpu(ghid->hdesc.wReportDescLength);
	if (!rsize || rsize > HID_MAX_DESCRIPTOR_SIZE) {
		dbg_hid("weird size of report descriptor (%u)\n", rsize);
		return -EINVAL;
	}

	rdesc = kzalloc(rsize, GFP_KERNEL);
	if (!rdesc) {
		return -ENOMEM;
	}

	ret = gb_hid_get_report_desc(ghid, rdesc);
	if (ret) {
		hid_err(hid, "reading report descriptor failed\n");
		goto free_rdesc;
	}

	ret = hid_parse_report(hid, rdesc, rsize);
	if (ret)
		dbg_hid("parsing report descriptor failed\n");

free_rdesc:
	kfree(rdesc);

	return ret;
}