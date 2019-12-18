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
struct ishtp_hid_data {int request_done; size_t raw_buf_size; int raw_get_req; int /*<<< orphan*/ * raw_buf; } ;
struct hostif_msg {int dummy; } ;
struct hid_device {struct ishtp_hid_data* driver_data; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned char HID_OUTPUT_REPORT ; 
#define  HID_REQ_GET_REPORT 129 
#define  HID_REQ_SET_REPORT 128 
 int /*<<< orphan*/  hid_hw_wait (struct hid_device*) ; 
 int /*<<< orphan*/  hid_ishtp_get_report (struct hid_device*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  hid_ishtp_set_feature (struct hid_device*,char*,size_t,unsigned char) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int ishtp_raw_request(struct hid_device *hid, unsigned char reportnum,
			     __u8 *buf, size_t len, unsigned char rtype,
			     int reqtype)
{
	struct ishtp_hid_data *hid_data =  hid->driver_data;
	char *ishtp_buf = NULL;
	size_t ishtp_buf_len;
	unsigned int header_size = sizeof(struct hostif_msg);

	if (rtype == HID_OUTPUT_REPORT)
		return -EINVAL;

	hid_data->request_done = false;
	switch (reqtype) {
	case HID_REQ_GET_REPORT:
		hid_data->raw_buf = buf;
		hid_data->raw_buf_size = len;
		hid_data->raw_get_req = true;

		hid_ishtp_get_report(hid, reportnum, rtype);
		break;
	case HID_REQ_SET_REPORT:
		/*
		 * Spare 7 bytes for 64b accesses through
		 * get/put_unaligned_le64()
		 */
		ishtp_buf_len = len + header_size;
		ishtp_buf = kzalloc(ishtp_buf_len + 7, GFP_KERNEL);
		if (!ishtp_buf)
			return -ENOMEM;

		memcpy(ishtp_buf + header_size, buf, len);
		hid_ishtp_set_feature(hid, ishtp_buf, ishtp_buf_len, reportnum);
		kfree(ishtp_buf);
		break;
	}

	hid_hw_wait(hid);

	return len;
}