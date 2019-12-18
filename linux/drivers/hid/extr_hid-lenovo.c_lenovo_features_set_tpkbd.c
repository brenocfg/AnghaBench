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
struct lenovo_drvdata_tpkbd {int sensitivity; int press_speed; scalar_t__ select_right; scalar_t__ release_to_select; scalar_t__ dragging; scalar_t__ press_to_select; } ;
struct hid_report {TYPE_2__** field; } ;
struct hid_device {TYPE_1__* report_enum; } ;
struct TYPE_4__ {int* value; } ;
struct TYPE_3__ {struct hid_report** report_id_hash; } ;

/* Variables and functions */
 size_t HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 struct lenovo_drvdata_tpkbd* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_request (struct hid_device*,struct hid_report*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lenovo_features_set_tpkbd(struct hid_device *hdev)
{
	struct hid_report *report;
	struct lenovo_drvdata_tpkbd *data_pointer = hid_get_drvdata(hdev);

	report = hdev->report_enum[HID_FEATURE_REPORT].report_id_hash[4];

	report->field[0]->value[0]  = data_pointer->press_to_select   ? 0x01 : 0x02;
	report->field[0]->value[0] |= data_pointer->dragging          ? 0x04 : 0x08;
	report->field[0]->value[0] |= data_pointer->release_to_select ? 0x10 : 0x20;
	report->field[0]->value[0] |= data_pointer->select_right      ? 0x80 : 0x40;
	report->field[1]->value[0] = 0x03; // unknown setting, imitate windows driver
	report->field[2]->value[0] = data_pointer->sensitivity;
	report->field[3]->value[0] = data_pointer->press_speed;

	hid_hw_request(hdev, report, HID_REQ_SET_REPORT);
	return 0;
}