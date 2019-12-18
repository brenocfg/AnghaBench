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
struct TYPE_4__ {int touch_max; } ;
struct hid_data {int num_expected; scalar_t__ cc_report; int cc_index; unsigned int cc_value_index; } ;
struct wacom_wac {TYPE_2__ features; struct hid_data hid_data; } ;
struct wacom {struct wacom_wac wacom_wac; } ;
struct hid_usage {size_t collection_index; int /*<<< orphan*/  hid; } ;
struct hid_report {int maxfield; scalar_t__ id; struct hid_field** field; } ;
struct hid_field {unsigned int maxusage; int* value; struct hid_usage* usage; } ;
struct hid_device {TYPE_1__* collection; } ;
struct TYPE_3__ {unsigned int level; } ;

/* Variables and functions */
 scalar_t__ HID_DG_CONTACTCOUNT ; 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 scalar_t__ wacom_equivalent_usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wacom_set_num_expected(struct hid_device *hdev,
				   struct hid_report *report,
				   int collection_index,
				   struct hid_field *field,
				   int field_index)
{
	struct wacom *wacom = hid_get_drvdata(hdev);
	struct wacom_wac *wacom_wac = &wacom->wacom_wac;
	struct hid_data *hid_data = &wacom_wac->hid_data;
	unsigned int original_collection_level =
		hdev->collection[collection_index].level;
	bool end_collection = false;
	int i;

	if (hid_data->num_expected)
		return;

	// find the contact count value for this segment
	for (i = field_index; i < report->maxfield && !end_collection; i++) {
		struct hid_field *field = report->field[i];
		unsigned int field_level =
			hdev->collection[field->usage[0].collection_index].level;
		unsigned int j;

		if (field_level != original_collection_level)
			continue;

		for (j = 0; j < field->maxusage; j++) {
			struct hid_usage *usage = &field->usage[j];

			if (usage->collection_index != collection_index) {
				end_collection = true;
				break;
			}
			if (wacom_equivalent_usage(usage->hid) == HID_DG_CONTACTCOUNT) {
				hid_data->cc_report = report->id;
				hid_data->cc_index = i;
				hid_data->cc_value_index = j;

				if (hid_data->cc_report != 0 &&
				    hid_data->cc_index >= 0) {

					struct hid_field *field =
						report->field[hid_data->cc_index];
					int value =
						field->value[hid_data->cc_value_index];

					if (value)
						hid_data->num_expected = value;
				}
			}
		}
	}

	if (hid_data->cc_report == 0 || hid_data->cc_index < 0)
		hid_data->num_expected = wacom_wac->features.touch_max;
}