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
struct hid_report {int maxfield; TYPE_2__** field; } ;
struct hid_device {TYPE_1__* report_enum; } ;
struct TYPE_4__ {int report_count; scalar_t__* value; } ;
struct TYPE_3__ {struct hid_report** report_id_hash; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  HID_REQ_GET_REPORT ; 
 int /*<<< orphan*/  hid_hw_request (struct hid_device*,struct hid_report*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_hw_wait (struct hid_device*) ; 

__attribute__((used)) static inline int ntrig_get_mode(struct hid_device *hdev)
{
	struct hid_report *report = hdev->report_enum[HID_FEATURE_REPORT].
				    report_id_hash[0x0d];

	if (!report || report->maxfield < 1 ||
	    report->field[0]->report_count < 1)
		return -EINVAL;

	hid_hw_request(hdev, report, HID_REQ_GET_REPORT);
	hid_hw_wait(hdev);
	return (int)report->field[0]->value[0];
}