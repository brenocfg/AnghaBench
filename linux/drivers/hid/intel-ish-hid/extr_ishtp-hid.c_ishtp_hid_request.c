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
struct ishtp_hid_data {int request_done; int raw_get_req; } ;
struct hostif_msg {int dummy; } ;
struct hid_report {int size; scalar_t__ id; int /*<<< orphan*/  type; } ;
struct hid_device {struct ishtp_hid_data* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  HID_REQ_GET_REPORT 129 
#define  HID_REQ_SET_REPORT 128 
 int /*<<< orphan*/  hid_ishtp_get_report (struct hid_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_ishtp_set_feature (struct hid_device*,char*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  hid_output_report (struct hid_report*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ishtp_hid_request(struct hid_device *hid, struct hid_report *rep,
	int reqtype)
{
	struct ishtp_hid_data *hid_data =  hid->driver_data;
	/* the specific report length, just HID part of it */
	unsigned int len = ((rep->size - 1) >> 3) + 1 + (rep->id > 0);
	char *buf;
	unsigned int header_size = sizeof(struct hostif_msg);

	len += header_size;

	hid_data->request_done = false;
	switch (reqtype) {
	case HID_REQ_GET_REPORT:
		hid_data->raw_get_req = false;
		hid_ishtp_get_report(hid, rep->id, rep->type);
		break;
	case HID_REQ_SET_REPORT:
		/*
		 * Spare 7 bytes for 64b accesses through
		 * get/put_unaligned_le64()
		 */
		buf = kzalloc(len + 7, GFP_KERNEL);
		if (!buf)
			return;

		hid_output_report(rep, buf + header_size);
		hid_ishtp_set_feature(hid, buf, len, rep->id);
		kfree(buf);
		break;
	}
}