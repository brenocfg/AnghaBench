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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct wacom_wac {size_t mode_report; size_t mode_value; } ;
struct hid_report_enum {struct hid_report** report_id_hash; } ;
struct hid_report {int dummy; } ;
struct hid_device {struct hid_report_enum* report_enum; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  WAC_MSG_RETRIES ; 
 size_t* hid_alloc_report_buf (struct hid_report*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_report_len (struct hid_report*) ; 
 int /*<<< orphan*/  kfree (size_t*) ; 
 int wacom_get_report (struct hid_device*,size_t,size_t*,int /*<<< orphan*/ ,int) ; 
 int wacom_set_report (struct hid_device*,size_t,size_t*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wacom_set_device_mode(struct hid_device *hdev,
				 struct wacom_wac *wacom_wac)
{
	u8 *rep_data;
	struct hid_report *r;
	struct hid_report_enum *re;
	u32 length;
	int error = -ENOMEM, limit = 0;

	if (wacom_wac->mode_report < 0)
		return 0;

	re = &(hdev->report_enum[HID_FEATURE_REPORT]);
	r = re->report_id_hash[wacom_wac->mode_report];
	if (!r)
		return -EINVAL;

	rep_data = hid_alloc_report_buf(r, GFP_KERNEL);
	if (!rep_data)
		return -ENOMEM;

	length = hid_report_len(r);

	do {
		rep_data[0] = wacom_wac->mode_report;
		rep_data[1] = wacom_wac->mode_value;

		error = wacom_set_report(hdev, HID_FEATURE_REPORT, rep_data,
					 length, 1);
		if (error >= 0)
			error = wacom_get_report(hdev, HID_FEATURE_REPORT,
			                         rep_data, length, 1);
	} while (error >= 0 &&
		 rep_data[1] != wacom_wac->mode_report &&
		 limit++ < WAC_MSG_RETRIES);

	kfree(rep_data);

	return error < 0 ? error : 0;
}